#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

typedef struct point_aux{
	int x;
	int y;
	float prob;
}point;

typedef struct segment_aux{
	point start;
	point end;
	int n_inliers; 
}segment;

//global variables
int n, m, limit_particles;
float sigma;
float mx, my;

point blocked[10000];
int n_blocked;

char directions[4];

point particles[1000];
int n_particles;

bool isNumber(char *str);
void ignoreComments();
bool isBlocked(point a);
point applyAction(point current, int action);
point getRandomPoint();
char convertCmd(char *command);
void startParticles();
void moveParticles(char cmd);
void weightParticles();
float measureParticle(point p);
void resampleParticles();
void printParticles();
