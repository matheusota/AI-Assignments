#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char **argv){
	int i, j, a, dirt, x, y;
	int limit;
	dirt = 0;
	generated = 1;
	expanded = 0;
	
	//scan the size of the matrix
	scanf("%d %d", &m, &n);
	
	limit = 2*m*n;
	
	//scan the matrix itself
	getchar();
	for(i = 0; i < n; i++){
		
		for(j = 0; j < m; j++){
			w[i][j] = getchar();
			
			//if it is the robot start position
			if(w[i][j] == '@'){
				x = j;
				y = i;
			}
			
			//counts the number of dirt and inserts in the list of dirts
			if(w[i][j] == '*'){
				insertListDirt(j, i);
				dirt++;
			}
		}
		
		//throw away break line
		a = getchar();
	}
	
	//executes dfs algorithm
	if(strcmp(argv[1], "depth-first") == 0){
		if(dirt > 0){
			if(dfs(x, y, dirt, 0, limit) == 1){
				printList();
				printf("%d nodes generated\n", generated);
				printf("%d nodes expanded\n", expanded);
			}
			else
				printf("no solution found\n");
		}
		//no dirt in the matrix, there is nothing to do
		else{
			printf("%d nodes generated\n", generated);
			printf("%d nodes expanded\n", expanded);
		}
	}
	
	//executes iterative dfs
	else if(strcmp(argv[1], "depth-first-id") == 0){
		if(dirt > 0){
			for(i = 0; i < limit && dfs(x, y, dirt, 0, i) == 0; i++);
			
			printList();
			printf("%d nodes generated\n", generated);
			printf("%d nodes expanded\n", expanded);
		}
		//no dirt in the matrix, there is nothing to do
		else{
			printf("%d nodes generated\n", generated);
			printf("%d nodes expanded\n", expanded);
		}
	}
	
	//executes djikstra algorithm
	else if(strcmp(argv[1], "uniform-cost") == 0)
		printAstar(x, y, dirt, 0);
		
	//executes a-star algorithm
	else if(strcmp(argv[1], "a-star") == 0){
		if(argv[2] == NULL)
			printf("Missing heuristic\n");
		else if(strcmp(argv[2], "h0") == 0)
			printAstar(x, y, dirt, 0);
		else if(strcmp(argv[2], "h1") == 0)
			printAstar(x, y, dirt, 1);
		else if(strcmp(argv[2], "h2") == 0)
			printAstar(x, y, dirt, 2);
		else
			printf("Unknown heuristic\n");
	}
	//unknown command
	else
		printf("command unknown\n");
	
	return 0;
}
