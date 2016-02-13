#!/usr/bin/env python

from __future__ import print_function
import pygame
from pygame import gfxdraw
import time
import sys
import math
import random
from subprocess import Popen, PIPE
import argparse

__author__ = 'Bence Cserna'

# Maximum window size
MAX_X = 800
MAX_Y = 800

# Basic colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)

# Univerisy of New Hampshire brand colors
BRAND_DARK = (37, 55, 70)
BRAND_LIGHT1 = (162, 170, 173)
BRAND_LIGHT2 = (214, 210, 196)
BRAND_ORANGE = (247, 122, 05)
# !/usr/bin/env python

DISTANCE_THRESHOLD = 0.01
STDEV = 2

global_screen = None


def error(*objs):
    print("ERROR: ", *objs, file=sys.stderr)


def debug(*objs):
    print("DEBUG: ", *objs, file=sys.stdout)


def filter_input(lines):
    return [line for line in lines if not line.startswith('/') and len(line) > 0]


def add_noise(signal, sigma):
    return signal + random.gauss(0, sigma)


class Node:
    def __init__(self, parent, state_vars, control=None):
        # (pos x, pos y, vel x, vel y)
        self.control = control
        self.state_vars = state_vars
        self.parent = parent

    @staticmethod
    def distance(lhs, rhs, sampling_bounds):
        vars = zip(lhs.state_vars, rhs.state_vars, sampling_bounds)
        cubed_state_vars = [((var[0] - var[1] - var[2][0]) / (var[2][1] - var[2][0])) ** 2 for var in vars]
        return math.sqrt(sum(cubed_state_vars))

    @staticmethod
    def same_state(lhs, rhs):
        vars = zip(lhs.state_vars[0:4], rhs.state_vars[0:4])
        cubed_state_vars = [(var[0] - var[1]) ** 2 for var in vars]
        return math.sqrt(sum(cubed_state_vars)) < DISTANCE_THRESHOLD

    def draw(self, screen, world, color=BRAND_LIGHT1):
        if not screen:
            return

        if self.parent:
            pygame.draw.aaline(screen,
                               color,
                               [int(self.parent.state_vars[0] * world.cell_size),
                                int((world.height - self.parent.state_vars[1]) * world.cell_size)],
                               [int(self.state_vars[0] * world.cell_size),
                                int((world.height - self.state_vars[1]) * world.cell_size)]
                               )
        else:
            pygame.gfxdraw.aacircle(screen,
                                    int(self.state_vars[0] * world.cell_size),
                                    int((world.height - self.state_vars[1]) * world.cell_size),
                                    2,
                                    color,
                                    )


class NodeStore:
    def __init__(self, sampling_bounds):
        self.sampling_bounds = sampling_bounds
        self.nodes = []
        self.mini_nodes = []

    def insert(self, node):
        self.nodes.append(node)

    def insert_mini(self, node):
        self.mini_nodes.append(node)

    def insert_minis(self, nodes):
        self.mini_nodes.extend(nodes)

    def remove(self, node):
        self.nodes.remove(node)

    def get_nodes(self):
        return self.nodes

    def get_mini_nodes(self):
        return self.mini_nodes

    def find_closest(self, target):
        distance_to_closest = float("inf")
        closest_node = None

        for node in self.nodes:
            distance = Node.distance(target, node, self.sampling_bounds)
            if distance < distance_to_closest:
                distance_to_closest = distance
                closest_node = node

        return closest_node

    def draw(self, screen):
        for node in self.nodes:
            node.draw(screen)


class Agent:
    def __init__(self, world):
        self.world = world
        x, y = world.random_space()
        self.x = x
        self.y = y

    def draw(self, screen, color):
        pygame.gfxdraw.aacircle(screen,
                                int(self.x * self.world.cell_size) + self.world.cell_size / 2,
                                int((self.world.height - self.y) * self.world.cell_size) - self.world.cell_size / 2,
                                5,
                                color,
                                )

    def try_move(self, dx, dy):
        dx, dy = self.apply_motion_model(dx, dy)
        if not self.world.in_collision((self.x + dx, self.y + dy)):
            self.x += dx
            self.y += dy

    @staticmethod
    def apply_motion_model(dx, dy):
        uniform = random.uniform(0, 1)
        if uniform < 0.7:
            return dx, dy
        elif uniform < 0.8:
            return dx * math.cos(math.pi / 2.0) - dy * math.sin(math.pi / 2.0), \
                   dx * math.sin(math.pi / 2.0) + dy * math.cos(math.pi / 2.0)
        elif uniform < 0.9:
            return dx * math.cos(-math.pi / 2.0) - dy * math.sin(-math.pi / 2.0), \
                   dx * math.sin(-math.pi / 2.0) + dy * math.cos(-math.pi / 2.0)
        else:
            return 0, 0

    def move_up(self):
        self.try_move(0, 1)

    def move_down(self):
        self.try_move(0, -1)

    def move_left(self):
        self.try_move(-1, 0)

    def move_right(self):
        self.try_move(1, 0)


class World:
    def __init__(self):
        self.obstacles = []
        self.obstacle_lookup = set()
        self.width = 0
        self.height = 0
        self.cell_size = 0
        self.start = ()
        self.goal = ()
        self.step_size = 0
        self.raw_input = None

    def __hash_cell(self, x, y):
        return int(y * self.width + x)

    def parse_world(self):
        input_lines = sys.stdin.readlines()

        if len(input_lines) == 0:
            sys.stderr.write("Error: Invalid input.\n")
            sys.stderr.flush()
            sys.exit()

        filtered_input = filter_input(input_lines)

        self.width = int(filtered_input.pop(0).strip())
        self.height = int(filtered_input.pop(0).strip())

        self.cell_size = min(MAX_X / self.width, MAX_Y / self.height)

        for y in xrange(0, self.height):
            line = filtered_input[y]

            for x in xrange(0, self.width):
                if line[x] is "#":
                    self.obstacles.append([x, y])
                    self.obstacle_lookup.add(self.__hash_cell(x, self.height - 1 - y))

        self.raw_input = input_lines
        return filter_input(input_lines)

    def random_space(self):
        while True:
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)
            if not self.in_collision((x, y)):
                return x, y

    def get_obstacles(self):
        return self.obstacles

    def draw(self, screen):
        if not screen:
            return

        for obstacle in self.obstacles:
            pygame.draw.rect(screen, BRAND_ORANGE, (
                obstacle[0] * self.cell_size,
                obstacle[1] * self.cell_size,
                self.cell_size,
                self.cell_size),
                             0)

        pygame.draw.rect(screen, BRAND_ORANGE, (
            0,
            0,
            self.width * self.cell_size,
            self.height * self.cell_size),
                         1)

    def draw_particles(self, screen, particles, color):
        collapsed_particles = {}

        grid_weight = [[0.0 for y in range(self.height)] for x in xrange(0, self.width)]
        grid_count = [[0.0 for y in range(self.height)] for x in xrange(0, self.width)]

        # guess = [0, 0, 0]
        weight_sum = 0.00000001
        for particle in particles:
            grid_weight[particle[0]][particle[1]] = grid_weight[particle[0]][particle[1]] + particle[2]
            grid_count[particle[0]][particle[1]] += 1
            weight_sum += particle[2]

            # if particle[2] >= guess[2]:
            #     guess = particle

        # pygame.draw.rect(screen, BRAND_ORANGE, (
        #     guess[0] * self.cell_size,
        #     guess[1] * self.cell_size,
        #     self.cell_size / 2,
        #     self.cell_size / 2),
        #                  0)

        if len(particles) > 0:
            for x in xrange(0, self.width):
                for y in xrange(0, self.height):
                    if grid_count[x][y] > 1:
                        pygame.gfxdraw.aacircle(screen,
                                                int(x * self.cell_size) + self.cell_size / 2,
                                                int((self.height - y) * self.cell_size) - self.cell_size / 2,
                                                2 + int(self.cell_size * grid_count[x][y] * 1.0 / len(particles)),
                                                RED,
                                                )
                        pygame.gfxdraw.aacircle(screen,
                                                int(x * self.cell_size) + self.cell_size / 2,
                                                int((self.height - y) * self.cell_size) - self.cell_size / 2,
                                                int(self.cell_size * grid_weight[x][y] / weight_sum),
                                                color,
                                                )

        for particle in particles:
            x, y = particle[0:2]
            pygame.gfxdraw.aacircle(screen,
                                    int(x * self.cell_size) + self.cell_size / 2,
                                    int((self.height - y) * self.cell_size) - self.cell_size / 2,
                                    2,
                                    color,
                                    )

    def in_collision(self, location):
        hash_value = self.__hash_cell(math.floor(location[0]), math.floor(location[1]))
        return self.__out_of_range(location) or self.obstacle_lookup.__contains__(hash_value)

    def __out_of_range(self, location):
        return location[0] < 0 or location[1] < 0 or location[0] >= self.width or location[1] >= self.height


def handle_input():
    if global_screen:
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN and (
                                    event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_UP or event.key == pygame.K_DOWN):
                return event.key
    return None


def initialize_world():
    world = World()
    filtered_input = world.parse_world()
    return world, filtered_input


def initialize_screen(world):
    pygame.init()
    pygame.display.set_caption('Particle Game')
    screen = pygame.display.set_mode((world.width * world.cell_size,
                                      world.height * world.cell_size))

    global global_screen
    global_screen = screen

    return screen


def apply_motion_model(dx, dy):
    uniform = random.uniform(0, 1)
    if uniform < 0.7:
        return dx, dy
    elif uniform < 0.8:
        return dx * math.cos(math.pi / 2.0) - dy * math.sin(math.pi / 2.0), \
               dx * math.sin(math.pi / 2.0) + dy * math.cos(math.pi / 2.0)
    elif uniform < 0.9:
        return dx * math.cos(-math.pi / 2.0) - dy * math.sin(-math.pi / 2.0), \
               dx * math.sin(-math.pi / 2.0) + dy * math.cos(-math.pi / 2.0)
    else:
        return 0, 0


def direction(direction):
    if direction in "NORTH":
        return 0, 1
    elif direction in "SOUTH":
        return 0, -1
    elif direction in "WEST":
        return -1, 0
    elif direction in "EAST":
        return 1, 0
    else:
        error("Invalid control!")
        sys.exit(-1)


def send_observation(x, y, control_text, world):
    print("%f %f %s" % (x, y, control_text))
    global particles

    # Initialize
    # if len(particles) == 0:
    #     for _ in xrange(0, 100):
    #         x, y = world.random_space()
    #         particles.append([x, y, 1])
    #     return particles

    original_dx, original_dy = direction(control_text)

    # Move
    for particle in particles:
        dx, dy = apply_motion_model(original_dx, original_dy)
        if not world.in_collision((particle[0] + dx, particle[1] + dy)):
            particle[0] = particle[0] + dx
            particle[1] = particle[1] + dy

    return particles


def process_observation(control, agent, world, sigma):
    control_text = ""

    if control == pygame.K_UP:
        agent.move_up()
        control_text = "NORTH"
    elif control == pygame.K_DOWN:
        agent.move_down()
        control_text = "SOUTH"
    elif control == pygame.K_LEFT:
        agent.move_left()
        control_text = "WEST"
    elif control == pygame.K_RIGHT:
        agent.move_right()
        control_text = "EAST"
    else:
        error("Invalid control!")
        sys.exit(-1)

    return add_noise(agent.x, sigma), add_noise(agent.y, sigma), control_text


def main():
    parser = argparse.ArgumentParser(description="CS730/830 Assignment #3")
    parser.add_argument("executable")
    parser.add_argument("-v", "--visuals", action="store_true")
    parser.add_argument("-s", "--sigma", default=2)
    parser.add_argument("-p", "--particles", default=100)

    args = parser.parse_args()

    world, filtered_input = initialize_world()
    # screen = None
    # if args.visuals:
    screen = initialize_screen(world)
    agent = Agent(world)

    params = []
    params += ["--sigma %s" % args.sigma]
    args_particles = int(args.particles)
    params += ["--particles %s" % args_particles]
    cmd = [" ".join(["./" + args.executable] + params)]
    print(["CMD:: "] + cmd)
    process = Popen(cmd, stdin=PIPE, stdout=PIPE, shell=True)
    process.stdin.writelines(filtered_input)

    # particles = read_particles(args_particles, process)
    particles = []

    sigma = float(args.sigma)

    while True:
        control = handle_input()
        if control is not None:
            observation = process_observation(control, agent, world, sigma)
            x, y, control = observation
            message = "%f %f %s\n" % (x, y, control)
            print("OUT:: " + message)
            process.stdin.write(message)
            particles = read_particles(args_particles, process)

        screen.fill(BRAND_DARK)
        world.draw(screen)
        world.draw_particles(screen, particles, BRAND_ORANGE)
        agent.draw(screen, BRAND_LIGHT1)
        pygame.display.flip()

    pygame.quit()


def read_particles(particle_count, process):
    particles = []
    for _ in xrange(0, particle_count):
        split = process.stdout.readline().strip().split(" ")
        # print("Particle: " + str(split))
        particles.append([int(split[0]), int(split[1]), float(split[2])])
    return particles


if __name__ == "__main__":
    main()
