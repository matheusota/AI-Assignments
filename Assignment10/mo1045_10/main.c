#include "functions.h"

int main(int argc, char **argv){
	int i, j;
	char a;
	char* buffer;
	string aux1, aux2;
	size_t size = 0;
	
	//get first line
	getline(&buffer, &size, stdin);
	
	//get number of attributes
	sscanf(buffer, "%d %s %d %s %d", &n_attributes, aux1, &n_values, aux2, &n_classes);
	
	//jump next line
	getline(&buffer, &size, stdin);
	
	//scan each training data
	a = getchar();
	j = 0;
	while(a != '-'){
		if(a > 47 && a < 58){
			ungetc(a, stdin);
			
			//get type of the data
			scanf("%d", &training[j].class);
			
			//get the actual data
			for(i = 0 ; i < n_attributes; i++)
				scanf("%f", &training[j].array[i]);
			j++;
		}
		
		a = getchar();
	}
	n_training = j;
	
	//normalize if is knn
	if(strcmp(argv[1], "knn") == 0)
		normalizeData();
	
	//set alpha if is lms
	else if(strcmp(argv[1], "linear") == 0)
		alpha = 0.0001;
			
	//jump next line
	getline(&buffer, &size, stdin);
	
	//for each test data
	a = getchar();
	while(a != EOF){
		if(a > 47 && a < 58){
			ungetc(a, stdin);
					
			for(i = 0; i < n_attributes; i++){
				scanf("%f", &test.array[i]);
				
				//normalize test data if is knn
				if(strcmp(argv[1], "knn") == 0)
					test.array[i] = test.array[i] / variances[i];
			}
				
			//run k-nearest neighbors algorithm
			if(strcmp(argv[1], "knn") == 0){
				knn();
			}
			
			//run linear regression algorithm
			else if(strcmp(argv[1], "linear") == 0)
				linear();
			
			//print output
			printf("%d %f\n", test.class, confidence);
			fflush(stdout);
		}
			
			a = getchar();
	}
		
	return 0;
}
