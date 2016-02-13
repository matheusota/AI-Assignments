#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

typedef struct point_aux{
	float x;
	float y;
}point;

typedef struct segment_aux{
	point start;
	point end;
	int n_inliers; 
}segment;

//global variables
int n, m;

point data[1000];
int n_data;

segment segments[1000];
int n_segments;

void ransac();
void ignoreComments();
int getRandomPoint();
float getDistancePoint2Line(int x, int y, float slope, float intercept);
void findInliers(float slope, float intercept, point* inliers, int *n_inliers);
point projection(float slope, float intercept, point p);
segment getBiggestSegment(float slope, float intercept, point* inliers, int* n_inliers);
segment linearRegression(point* inliers, int* n_inliers);
void copyPoints(point* dest, point* source, int n_source);
void removeFromData(int index);
void removeInliers(segment s);
