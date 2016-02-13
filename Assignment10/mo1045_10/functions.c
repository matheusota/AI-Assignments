#include "functions.h"

//normalize data by dividing by the variance
void normalizeData(){
	int i, j;
	float sum, mean;
	
	for(i = 0; i < n_attributes; i++){
		//computes the mean
		sum = 0;
		for(j = 0; j < n_training; j++)
			sum += training[j].array[i];
		mean = sum / (float) n_training;
		
		//computes the variance
		variances[i] = 0;
		for(j = 0; j < n_training; j++)
			variances[i] += (training[j].array[i] - mean) * (training[j].array[i] - mean);
		variances[i] = sqrt(variances[i] / (float) n_training);
		
		//correction to dont divide by zero
		if(variances[i] == 0)
			variances[i] = 1;
		
		//divides each coordinate by the variance
		for(j = 0; j < n_training; j++)
			training[j].array[i] = training[j].array[i] / variances[i]; 
	}	
}

//computes the euclidean distance between two data sets
float distance(float *data1, float *data2){
	int i;
	float sum = 0;
	
	for(i = 0; i < n_attributes; i++)
		sum += (data1[i] - data2[i]) * (data1[i] - data2[i]);
	
	return sqrt(sum);
}

//find the index of the biggest value in the array
int findBiggest(float *array){
	int i, index;
	float biggest = 0;
	
	for(i = 0; i < K; i++){
		if(array[i] > biggest){
			biggest = array[i];
			index = i;
		}	
	}
	
	return index;
}

//find the index of the smalles value in the array
int findSmallest(float *array){
	int i, index;
	float smallest = INF;
	
	for(i = 0; i < K; i++){
		if(array[i] < smallest){
			smallest = array[i];
			index = i;
		}	
	}
	
	return index;
}

//counts the integer that appear most in the array
int countValues(int *array){
	int counting[n_classes], i, index, total = 0, biggest = 0;
	
	//initialize to 0
	for(i = 0; i < n_classes; i++)
		counting[i] = 0;
	
	//counts
	for(i = 0; i < K; i++){
		if(array[i] != -1){
			total++;
			counting[array[i]]++;
		}
	}
	
	//finds the biggest
	for(i = 0; i < n_classes; i++){
		if(counting[i] > biggest){
			biggest = counting[i];
			index = i;
		}
	}
	
	confidence = (float) biggest / (float) total;
	
	if(biggest == 1)
		return -1;
	else
		return index;
}

//implements the knn algorithm
void knn(){
	int i, type_small[K], big_small, class;
	float smallers[K], d;
	
	//initialize smallers with infinity
	//big_small holds the biggest value in the smallers array
	for(i = 0; i < K; i++){
		smallers[i] = INF;
		type_small[i] = -1;
	}
	big_small = 0;
	
	for(i = 0; i < n_training; i++){
		d = distance(training[i].array, test.array);
		
		if(d < smallers[big_small]){
			smallers[big_small] = d;
			type_small[big_small] = training[i].class;
			big_small = findBiggest(smallers);
		}
	}
	
	//big_small holds the smaller value in the smallers array
	big_small = findSmallest(smallers);
	
	class = countValues(type_small);
	
	if(class == -1)
		test.class = type_small[big_small];
	else
		test.class = class;
}

//lms algorithm or adaline algorithm for each class x
float lms(int x){
	int i, j, y;
	float prediction, parameters[n_attributes + 1];
	
	//initialize all parameters and prediction to 0
	for(i = 0; i < n_attributes + 1; i++)
		parameters[i] = 0;
	
	//for each member m of training set
	for(i = 0; i < n_training; i++){
		//y = 1 if m.class = x, else y = 0
		if(training[i].class == x)
			y = 1;
		else
			y = 0;
		
		//computes the prediction
		prediction = parameters[0];
		for(j = 1; j < n_attributes + 1; j++)
			prediction += parameters[j] * training[i].array[j - 1];
			
		//updates each parameter according to lms rule
		parameters[0] -= alpha * (prediction - y);
		for(j = 1; j < n_attributes + 1; j++)
			parameters[j] -= alpha * (prediction - y) * training[i].array[j - 1];
	}
	
	//computes the prediction
	prediction = parameters[0];
	for(j = 1; j < n_attributes + 1; j++)
		prediction += parameters[j] * test.array[j - 1];
	
	//return it		
	return prediction;
}

//call the lms algorithm for each class, return the biggest value
void linear(){
	int i, index;
	float result[n_classes], biggest = -INF, sum = 0;
	
	for(i = 0; i < n_classes; i++)
		result[i] = lms(i);
	
	//find the biggest result
	for(i = 0; i < n_classes; i++){
		sum += result[i];
		
		if(result[i] > biggest){
			biggest = result[i];
			index = i;
		}	
	}
	
	confidence = biggest / sum;
	
	test.class = index;
}
