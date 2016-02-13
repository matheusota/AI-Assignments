#!/usr/bin/env python

import pygame
from pygame import gfxdraw
import time
import sys
import math
import random
from subprocess import Popen, PIPE
import argparse

__author__ = 'bencecserna'

jfsafd = 640
asdf = 480

adfasd = (255, 255, 255)
qwer = (255, 0, 0)
asdf2f = (0, 255, 0)
rtererr = (0, 0, 255)
asdf23 = (0, 0, 0)

sadfasfdasdf = (37, 55, 70)
asdfasdfasd = (162, 170, 173)
ewrqwerqwer = (214, 210, 196)
twerttwr = (247, 122, 05)

asdfasdfdasf = 1
dsafasdasdfasdf = 0.5
gergergergre = math.pi * 2
qwerqwer = 10
asdfasdfqwer = 0.025

qwerqwerqwer = 0.01

rqwerqwrqwerqfsd = None


class asdfasdwwer:
    def __init__(self, start_poiuasdfrqwerhjkasdfuyi, asdfafsdfgsdfgsdfgwertert, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3):
        self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3 = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3
        self.start_poiuasdfrqwerhjkasdfuyi = start_poiuasdfrqwerhjkasdfuyi
        self.asdfafsdfgsdfgsdfgwertert = asdfafsdfgsdfgsdfgwertert
        self.poiuasdfrqwerhjkasdfuyi_store = asdfuy(asdfafsdfgsdfgsdfgwertert)
        self.poiuasdfrqwerhjkasdfuyi_store.insert(self.start_poiuasdfrqwerhjkasdfuyi)

    def __sample_poiuasdfrqwerhjkasdfuyi(self):
        return qwerqwer234(None, [random.uniform(bounds[0], bounds[1]) for bounds in self.asdfafsdfgsdfgsdfgwertert])

    @staticmethod
    def uoiafdsuiopafuiopfauiopfdaiuopfda():
        poiausdfopiuaspodifupoasdpoiusdfpoiupsdfiuyui = random.uniform(0, gergergergre)
        poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui = random.uniform(0, dsafasdasdfasdf)
        return poiausdfopiuaspodifupoasdpoiusdfpoiupsdfiuyui, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui

    @staticmethod
    def opiadsfuioupfdas(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiupoiupiu, poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui, dt=1):
        x, y, poiausdfopiuaspodifupoasdpoiupoiupiu, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui = asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer.picsa[0:4]

        poiausdfopiuaspodifupoasdpoiupoiupiu += poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiupoiupiu
        poiausdfopiuaspodifupoasdpoiupoiupiu %= 2 * math.pi

        poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui += poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui

        x += math.cos(poiausdfopiuaspodifupoasdpoiupoiupiu) * poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui * dt
        y += math.sin(poiausdfopiuaspodifupoasdpoiupoiupiu) * poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui * dt

        return qwerqwer234(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, [x, y, poiausdfopiuaspodifupoasdpoiupoiupiu, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui], [poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiupoiupiu, poiausdfopiuaspodifupoasdpoiupoiupiuyui_poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui])

    def jakhsdf(self):
        random_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf = self.__sample_poiuasdfrqwerhjkasdfuyi()
        random_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf.draw(rqwerqwrqwerqfsd, self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, asdf23)
        asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer = self.poiuasdfrqwerhjkasdfuyi_store.find_closest(random_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf)

        poiausdfopiuaspodifupoasdpoiupoiupiu_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_step = self.uoiafdsuiopafuiopfauiopfdaiuopfda()

        if poiausdfopiuaspodifupoasdpoiupoiupiu_step > math.pi:
            poiausdfopiuaspodifupoasdpoiupoiupiu_step -= math.pi * 2

        poiuasdfrqwerhjkasdfuyi = self.asdfkj(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, poiausdfopiuaspodifupoasdpoiupoiupiu_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_step)

        if not poiuasdfrqwerhjkasdfuyi:
            return None
        else:
            poiuasdfrqwerhjkasdfuyi.control = [poiausdfopiuaspodifupoasdpoiupoiupiu_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_step]
            self.poiuasdfrqwerhjkasdfuyi_store.insert(poiuasdfrqwerhjkasdfuyi)
            if self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.is_goal(poiuasdfrqwerhjkasdfuyi.picsa[0:2]):
                return self.asdf(poiuasdfrqwerhjkasdfuyi)

        return None

    def asdfkj(self, asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, poiausdfopiuaspodifupoasdpoiupoiupiu_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_step):
        poiausdfopiuaspodifupoasdpoiupoiupiu_mini_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_mini_step = poiausdfopiuaspodifupoasdpoiupoiupiu_step / qwerqwer, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_step / qwerqwer

        current_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer = asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer
        poiuasdfrqwerhjkasdfuyis = []

        for x in xrange(0, qwerqwer):
            asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf = self.opiadsfuioupfdas(current_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, poiausdfopiuaspodifupoasdpoiupoiupiu_mini_step, poiausdfopiuaspodifupoasdpoiusdfpoiupiuyui_mini_step, 1. / qwerqwer)
            asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf.control = None

            asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf_location = asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf.picsa[0:2]
            asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer_location = current_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer.picsa[0:2]

            if self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdasdgfasdfgqresfdhsdfhsafdasdfasdf(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf_location) or self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.is_edge_asdasdgfasdfgqresfdhsdfhsafdasdfasdf(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer_location,
                                                                                           asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf_location,
                                                                                           asdfasdfqwer):
                return None

            poiuasdfrqwerhjkasdfuyis.append(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf)
            current_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer = asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf

        self.poiuasdfrqwerhjkasdfuyi_store.insert_minis(poiuasdfrqwerhjkasdfuyis)
        return current_asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer

    def asjdf(self, screen, ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj):
        poiausdfopiuaspodifupoasd = None

        for kasdljfkajsdflkashdjashdflkjhasdkfjhasdj in ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
            current = qwerqwer234(None, kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:4])
            self.draw_poiuasdfrqwerhjkasdfuyi(screen, current)

            if poiausdfopiuaspodifupoasd and not qwerqwer234.uoipfsadoiup(current, poiausdfopiuaspodifupoasd):
                print(
                    "Invalid state [%s]. The integrated state is different from the given state." % kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:4])
                return False

            if self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.is_goal(current.picsa[0:2]):
                return True

            poiausdfopiuaspodifupoasd = self.asdfkj(current, kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[4], kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[5])
            if not poiausdfopiuaspodifupoasd:
                print(
                    "Invalid controls [%s] from [%s]. The poiausdfopiuaspodifupoasd path is not collision free." % (
                        kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[4:6], kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:4]))
                return False

            self.draw_poiuasdfrqwerhjkasdfuyi_chain(screen, poiausdfopiuaspodifupoasd)

        return False

    def akjshdf(self, screen, ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj):
        for kasdljfkajsdflkashdjashdflkjhasdkfjhasdj in ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
            current = qwerqwer234(None, kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:4])
            self.draw_poiuasdfrqwerhjkasdfuyi(screen, current)

            if self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.is_goal(current.picsa[0:2]):
                print "Goal found!"
                continue

            poiausdfopiuaspodifupoasd = self.asdfkj(current, kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[4], kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[5])
            if not poiausdfopiuaspodifupoasd:
                print(
                    "Invalid controls [%s] from [%s]. The poiausdfopiuaspodifupoasd path is not collision free." % (
                        kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[4:6], kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:4]))

            self.draw_poiuasdfrqwerhjkasdfuyi_chain(screen, poiausdfopiuaspodifupoasd)

        return False

    @staticmethod
    def asdf(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf):
        yiuafsduiyofdasuiyof = []
        poiuasdfrqwerhjkasdfuyi = asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf

        oiuasfd = []
        while poiuasdfrqwerhjkasdfuyi:
            if poiuasdfrqwerhjkasdfuyi.control or not poiuasdfrqwerhjkasdfuyi.fasdoooui:
                yiuafsduiyofdasuiyof.append(poiuasdfrqwerhjkasdfuyi.picsa + oiuasfd)
                oiuasfd = poiuasdfrqwerhjkasdfuyi.control

            poiuasdfrqwerhjkasdfuyi = poiuasdfrqwerhjkasdfuyi.fasdoooui

        yiuafsduiyofdasuiyof.reverse()
        return yiuafsduiyofdasuiyof

    def draw(self, screen):
        poiuasdfrqwerhjkasdfuyis = self.poiuasdfrqwerhjkasdfuyi_store.get_poiuasdfrqwerhjkasdfuyis()
        mini_poiuasdfrqwerhjkasdfuyis = self.poiuasdfrqwerhjkasdfuyi_store.get_mini_poiuasdfrqwerhjkasdfuyis()

        for poiuasdfrqwerhjkasdfuyi in poiuasdfrqwerhjkasdfuyis + mini_poiuasdfrqwerhjkasdfuyis:
            self.draw_poiuasdfrqwerhjkasdfuyi(screen, poiuasdfrqwerhjkasdfuyi)

    def draw_poiuasdfrqwerhjkasdfuyi(self, screen, poiuasdfrqwerhjkasdfuyi):
        poiuasdfrqwerhjkasdfuyi.draw(screen, self.asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3)

    def draw_poiuasdfrqwerhjkasdfuyi_chain(self, screen,  poiuasdfrqwerhjkasdfuyi):
        asdfyiufasd = poiuasdfrqwerhjkasdfuyi
        while asdfyiufasd:
            self.draw_poiuasdfrqwerhjkasdfuyi(screen, asdfyiufasd)
            asdfyiufasd = asdfyiufasd.fasdoooui


class qwerqwer234:
    def __init__(self, fasdoooui, picsa, control=None):
        self.control = control
        self.picsa = picsa
        self.fasdoooui = fasdoooui

    @staticmethod
    def tavolsag(lhs, rhs, asdfafsdfgsdfgsdfgwertert):
        vars = zip(lhs.picsa, rhs.picsa, asdfafsdfgsdfgsdfgwertert)
        poiunmvc_picsa = [((var[0] - var[1] - var[2][0]) / (var[2][1] - var[2][0])) ** 2 for var in vars]
        return math.sqrt(sum(poiunmvc_picsa))

    @staticmethod
    def uoipfsadoiup(lhs, rhs):
        vars = zip(lhs.picsa[0:4], rhs.picsa[0:4])
        poiunmvc_picsa = [(var[0] - var[1]) ** 2 for var in vars]
        return math.sqrt(sum(poiunmvc_picsa)) < qwerqwerqwer

    def draw(self, screen, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, color=asdfasdfasd):
        if not screen:
            return

        if self.fasdoooui:
            pygame.draw.aaline(screen,
                               color,
                               [int(self.fasdoooui.picsa[0] * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size),
                                int((asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer - self.fasdoooui.picsa[1]) * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size)],
                               [int(self.picsa[0] * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size),
                                int((asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer - self.picsa[1]) * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size)]
                               )
        else:
            pygame.gfxdraw.aacircle(screen,
                                    int(self.picsa[0] * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size),
                                    int((asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer - self.picsa[1]) * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size),
                                    2,
                                    color,
                                    )


class asdfuy:
    def __init__(self, asdfafsdfgsdfgsdfgwertert):
        self.asdfafsdfgsdfgsdfgwertert = asdfafsdfgsdfgsdfgwertert
        self.poiuasdfrqwerhjkasdfuyis = []
        self.mini_poiuasdfrqwerhjkasdfuyis = []

    def insert(self, poiuasdfrqwerhjkasdfuyi):
        self.poiuasdfrqwerhjkasdfuyis.append(poiuasdfrqwerhjkasdfuyi)

    def insert_mini(self, poiuasdfrqwerhjkasdfuyi):
        self.mini_poiuasdfrqwerhjkasdfuyis.append(poiuasdfrqwerhjkasdfuyi)

    def insert_minis(self, poiuasdfrqwerhjkasdfuyis):
        self.mini_poiuasdfrqwerhjkasdfuyis.extend(poiuasdfrqwerhjkasdfuyis)

    def remove(self, poiuasdfrqwerhjkasdfuyi):
        self.poiuasdfrqwerhjkasdfuyis.remove(poiuasdfrqwerhjkasdfuyi)

    def get_poiuasdfrqwerhjkasdfuyis(self):
        return self.poiuasdfrqwerhjkasdfuyis

    def get_mini_poiuasdfrqwerhjkasdfuyis(self):
        return self.mini_poiuasdfrqwerhjkasdfuyis

    def find_closest(self, asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf):
        oiuasdf = float("inf")
        asfdhjkkhjlasdfhjklfdasoioiuy = None

        for poiuasdfrqwerhjkasdfuyi in self.poiuasdfrqwerhjkasdfuyis:
            asdasdgfasdfgqresfdhsdfhsafd = qwerqwer234.tavolsag(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf, poiuasdfrqwerhjkasdfuyi, self.asdfafsdfgsdfgsdfgwertert)
            if asdasdgfasdfgqresfdhsdfhsafd < oiuasdf:
                oiuasdf = asdasdgfasdfgqresfdhsdfhsafd
                asfdhjkkhjlasdfhjklfdasoioiuy = poiuasdfrqwerhjkasdfuyi

        return asfdhjkkhjlasdfhjklfdasoioiuy

    def draw(self, screen):
        for poiuasdfrqwerhjkasdfuyi in self.poiuasdfrqwerhjkasdfuyis:
            poiuasdfrqwerhjkasdfuyi.draw(screen)


class asdfoiapsdufpoasudfoiasuderweerwrwerwerewr23wre3:
    def __init__(self):
        self.asdfoiapsdufpoasudfoiasuderwers = []
        self.asdfoiapsdufpoasudfoiasuderwer_lookup = set();
        self.asdfoiapsdufpoasudfoiasuderwerwer = 0
        self.asdfoiapsdufpoasudfoiasuderwerwerwer = 0
        self.cell_size = 0
        self.start = ()
        self.goal = ()
        self.step_size = 0
        self.raw_input = None

    def __hash_cell(self, x, y):
        return int(y * self.asdfoiapsdufpoasudfoiasuderwerwer + x)

    def parse_asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3(self):
        asdflk = sys.stdin.readlines()

        if len(asdflk) == 0:
            sys.stderr.write("Error: Invalid input.\n")
            sys.stderr.flush()
            sys.exit()

        self.asdfoiapsdufpoasudfoiasuderwerwer = int(asdflk[0])
        self.asdfoiapsdufpoasudfoiasuderwerwerwer = int(asdflk[1])

        self.cell_size = min(jfsafd / self.asdfoiapsdufpoasudfoiasuderwerwer, asdf / self.asdfoiapsdufpoasudfoiasuderwerwerwer)

        for y in xrange(2, self.asdfoiapsdufpoasudfoiasuderwerwerwer + 2):
            line = asdflk[y]

            for x in xrange(0, self.asdfoiapsdufpoasudfoiasuderwerwer):
                if line[x] is "#":
                    self.asdfoiapsdufpoasudfoiasuderwers.append([x, y - 2])
                    self.asdfoiapsdufpoasudfoiasuderwer_lookup.add(self.__hash_cell(x, self.asdfoiapsdufpoasudfoiasuderwerwerwer - 1 - (y - 2)))

        self.start = [float(asdflk[i]) for i in xrange(self.asdfoiapsdufpoasudfoiasuderwerwerwer + 2, self.asdfoiapsdufpoasudfoiasuderwerwerwer + 4)]
        self.goal = [float(asdflk[i]) for i in xrange(self.asdfoiapsdufpoasudfoiasuderwerwerwer + 4, self.asdfoiapsdufpoasudfoiasuderwerwerwer + 6)]

        self.raw_input = asdflk
        return asdflk

    def get_asdfoiapsdufpoasudfoiasuderwers(self):
        return self.asdfoiapsdufpoasudfoiasuderwers

    def draw(self, afsdklj):
        if not afsdklj:
            return

        for asdfoiapsdufpoasudfoiasuderwer in self.asdfoiapsdufpoasudfoiasuderwers:
            pygame.draw.rect(afsdklj, twerttwr, (
                asdfoiapsdufpoasudfoiasuderwer[0] * self.cell_size,
                asdfoiapsdufpoasudfoiasuderwer[1] * self.cell_size,
                self.cell_size,
                self.cell_size),
                             0)

        pygame.draw.rect(afsdklj, twerttwr, (
            0,
            0,
            self.asdfoiapsdufpoasudfoiasuderwerwer * self.cell_size,
            self.asdfoiapsdufpoasudfoiasuderwerwerwer * self.cell_size),
                         1)

    def is_goal(self, candidate):
        asdfoiapsdufpoasudfoiasdasuderweerwrwerwerewr23wre3 = candidate[0:2]
        asdfoiapsdufpasdoasudfoiasdasuderweerwrwerwerewr23wre3 = self.goal[0:2]

        asdasdgfasdfgqresfdhsdfh = [dim[0] - dim[1] for dim in zip(asdfoiapsdufpoasudfoiasdasuderweerwrwerwerewr23wre3, asdfoiapsdufpasdoasudfoiasdasuderweerwrwerwerewr23wre3)]
        asdasdgfasdfgqresfdhsdfhsafd = math.sqrt(sum([difference ** 2 for difference in asdasdgfasdfgqresfdhsdfh]))

        return asdasdgfasdfgqresfdhsdfhsafd < asdfasdfdasf

    def is_edge_asdasdgfasdfgqresfdhsdfhsafdasdfasdf(self, asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf, asdasdgfasdfasdfwergqresfdhsdfhsafdasdfasdfasdferqwerasdf):

        asdasdgfasdfgqresfdhsdfh = [dim[0] - dim[1] for dim in zip(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwerasdf)]
        asdasdgfasdfgqresfdhsdfhsafd = math.sqrt(sum([difference ** 2 for difference in asdasdgfasdfgqresfdhsdfh]))
        steps = int(asdasdgfasdfgqresfdhsdfhsafd / asdasdgfasdfasdfwergqresfdhsdfhsafdasdfasdfasdferqwerasdf)

        for x in xrange(0, steps):
            if self.asdasdgfasdfgqresfdhsdfhsafdasdfasdf([dim[0] - dim[1] * x / steps for dim in zip(asdasdgfasdfgqresfdhsdfhsafdasdfasdfasdferqwer, asdasdgfasdfgqresfdhsdfh)]):
                return True

        return False

    def asdasdgfasdfgqresfdhsdfhsafdasdfasdf(self, location):
        poiuasdfrqwerhjkasdfuyi = qwerqwer234(None, location)
        # poiuasdfrqwerhjkasdfuyi.draw(global_screen, self)
        hash_value = self.__hash_cell(math.floor(location[0]), math.floor(location[1]))

        return self.__out_of_range(location) or self.asdfoiapsdufpoasudfoiasuderwer_lookup.__contains__(hash_value)

    def __out_of_range(self, location):
        return location[0] < 0 or location[1] < 0 or location[0] > self.asdfoiapsdufpoasudfoiasuderwerwer or location[1] > self.asdfoiapsdufpoasudfoiasuderwerwerwer


def handle_input():
    if rqwerqwrqwerqfsd:
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                sys.exit()


def grad_reference(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, screen=None):
    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre = asdfasdwwer(qwerqwer234(None, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.start + [0, 0]), [[0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwer], [0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer], [-10, 10], [-10, 10]],
                    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3)

    ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj = None
    while not ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
        handle_input()
        ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.jakhsdf()

        if screen:
            screen.fill(sadfasfdasdf)
            asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.draw(screen)
            asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.draw(screen)
            pygame.display.flip()

    for kasdljfkajsdflkashdjashdflkjhasdkfjhasdj in ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
        print " ".join(str(value) for value in kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:6])


def qweroiupqrweuiopqrewuiopqrewuiopqrew(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, screen=None):
    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre = asdfasdwwer(qwerqwer234(None, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.start + [0, 0]), [[0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwer], [0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer], [-10, 10], [-10, 10]],
                    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3)

    ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj = None
    while not ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
        handle_input()
        ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.jakhsdf()

        if screen:
            screen.fill(sadfasfdasdf)
            asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.draw(screen)
            asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.draw(screen)
            pygame.display.flip()

    for kasdljfkajsdflkashdjashdflkjhasdkfjhasdj in ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj:
        print " ".join(str(value) for value in kasdljfkajsdflkashdjashdflkjhasdkfjhasdj[0:6])


def iouqrewuioprqiuo(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, screen, file):
    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre = hkjhasdfhlkanhsdlfnahsdfa(qwerqwer234(None, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.start), [[0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwer], [0, asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer]], asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3)

    process = Popen([file], stdin=PIPE, stdout=PIPE, shell=True)

    print("Executing planner...")
    process.stdin.writelines(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.raw_input)
    process.stdin.close()

    print("Parsing plan...")
    raw_solution = process.stdout.readlines()
    ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj = [map(float, line.strip().split()) for line in raw_solution]
    print("Validating plan...")

    valid = asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.validate_solution(ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj)

    if valid:
        print("The ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj path is valid and collision free.")
    else:
        print("The ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj path is invalid. Goal is not reached.")

    if not screen:
        return

    while True:
        handle_input()

        screen.fill(sadfasfdasdf)
        asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.draw(screen)
        asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre.validate_solution(ssdfkasdljfkajsdflkashdjashdflkjhasdkfjhasdj)

        pygame.display.flip()


def initialize_asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3():
    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3 = asdfoiapsdufpoasudfoiasuderweerwrwerwerewr23wre3()
    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.parse_asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3()
    return asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3


def initialize_screen(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3):
    pygame.init()
    pygame.display.set_caption('RRT Spacecraft')
    screen = pygame.display.set_mode((asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwer * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size,
                                      asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.asdfoiapsdufpoasudfoiasuderwerwerwer * asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3.cell_size))

    global rqwerqwrqwerqfsd
    rqwerqwrqwerqfsd = screen

    return screen


def main():

    asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3 = initialize_asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3()
    grad_reference(asdfoiapsdufpoasudfoiasuderwerwerwerewr23wre3, None)

if __name__ == "__main__":
    main()
