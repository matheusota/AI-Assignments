#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define K 5
#define INF 99999

//string type
typedef char string[100];

typedef struct data_aux{
	float array[1000];
	int class;
}node_data;

//global variables
int n_attributes, n_values, n_classes, n_training;
node_data test, training[70000];
float confidence, alpha, variances[1000];

void normalizeData();
float distance(float *data1, float *data2);
int findBiggest(float *array);
int findSmallest(float *array);
void knn();

float lms(int x);
void linear();

