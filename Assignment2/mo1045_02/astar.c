#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*implements A* algorithm*/
tree astar(int x, int y, int d, int heuristic){
	char a = 'X';//X simbolize that no action was taken to get there
	tree t, t1, t2;
	char **mat1, **mat2;
	int i, j;
	int level;
	double f;
	queue_vector aux;
	int k;
	
	//copy the starting matrix
	mat1 = newMatrix();
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			mat1[i][j] = w[i][j];
	}
	
	t1 = insertTree(NULL, d, x, y, mat1, a, 0);
	t = t1;
	
	//compute the f value according to the heuristic
	f = computeHeuristic(x, y, 0, heuristic);
	
	insertQueue(t1, f);
	
	while(n_queue > 0){
		//remove the first element of the queue
		removeQueue(&aux.t, &aux.f);
		t1 = aux.t;
		
		d = t1 -> dirt;
		mat1 = t1 -> mat;
		a = t1 -> action;
		x = t1 -> x;
		y = t1 -> y;
		level = t1 -> level;
		
		//increments the number of nodes expanded
		expanded++;
		
		//adds into the queue
		if(y != 0 && mat1[y-1][x] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y-1][x];
			
			mat2[y-1][x] = '@';
			mat2[y][x] = '_';
			
			if(a == '*')
				k = d-1;
			else
				k = d;
			
			if(checkDuplicate(t, mat2, hashFunction(x, y-1), k) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*'){
					removeListDirt(x, y-1);
					t2 = insertTree(t1, d-1, x, y-1, mat2, 'n', level + 1);
					
					if(d-1 == 0)
						return t2;
				}
				else
					t2 = insertTree(t1, d, x, y-1, mat2, 'N', level + 1);
					
				t1 -> N = t2;
				
				//compute the f value according to the heuristic
				f = computeHeuristic(x, y-1, level+1, heuristic);
					
				insertQueue(t2, f);
				generated++;
			}
		}
			
		if(y != n - 1 && mat1[y+1][x] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y+1][x];
			
			mat2[y+1][x] = '@';
			mat2[y][x] = '_';
			
			if(a == '*')
				k = d-1;
			else
				k = d;
			
			if(checkDuplicate(t, mat2, hashFunction(x, y+1), k) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*'){
					removeListDirt(x, y+1);
					t2 = insertTree(t1, d-1, x, y+1, mat2, 's', level + 1);
					
					if(d-1 == 0)
						return t2;
				}
				else
					t2 = insertTree(t1, d, x, y+1, mat2, 'S', level + 1);
				
				t1 -> S = t2;
				
				//compute the f value according to the heuristic
				f = computeHeuristic(x, y-1, level+1, heuristic);
				
				insertQueue(t2, f);
				generated++;
			}
		}
		
		if(x != 0 && mat1[y][x-1] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y][x-1];
			
			mat2[y][x-1] = '@';
			mat2[y][x] = '_';
			
			if(a == '*')
				k = d-1;
			else
				k = d;
			
			if(checkDuplicate(t, mat2, hashFunction(x - 1, y), k) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*'){
					removeListDirt(x-1, y);
					t2 = insertTree(t1, d-1, x-1, y, mat2, 'w', level + 1);
					
					if(d-1 == 0)
						return t2;
				}
				else
					t2 = insertTree(t1, d, x-1, y, mat2, 'W', level + 1);
					
				t1 -> W = t2;
				
				//compute the f value according to the heuristic
				f = computeHeuristic(x, y-1, level+1, heuristic);
					
				insertQueue(t2, f);
				generated++;
			}
		}
		
		if(x != m - 1 && mat1[y][x+1] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y][x+1];
			
			mat2[y][x+1] = '@';
			mat2[y][x] = '_';
			
			if(a == '*')
				k = d-1;
			else
				k = d;
			
			if(checkDuplicate(t, mat2, hashFunction(x + 1, y), k) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*'){
					removeListDirt(x+1, y);
					t2 = insertTree(t1, d-1, x+1, y, mat2, 'e', level + 1);
					
					if(d-1 == 0)
						return t2;
				}
				else
					t2 = insertTree(t1, d, x+1, y, mat2, 'E', level + 1);
					
				t1 -> E = t2;
				
				//compute the f value according to the heuristic
				f = computeHeuristic(x, y-1, level+1, heuristic);
				
				insertQueue(t2, f);
				generated++;
			}
		}
		
		orderQueue();
	}
	
	return NULL;
}

//prints the path of the a-star
void printAstar(int x, int y, int dirt, int heuristic){
	tree t;
	
	if(dirt > 0){
		t = astar(x, y, dirt, heuristic);

		if(t == NULL)
			printf("no solution found\n");
		
		else{
			//inserts the actions in a list
			while(t -> action != 'X'){
				//lowercase mean it can vacuum
				if(t -> action > 96){
					insertList('V');
					t -> action = t -> action - 32;
				}
				
				//inserts in the list
				insertList(t -> action);
				
				t = t -> parent;
			}
			
			//free the memory
			freeTree(t);
			
			//print it
			printList();
			printf("%d nodes generated\n", generated);
			printf("%d nodes expanded\n", expanded);
		}
	}
	//no dirt in the matrix, there is nothing to do
	else{
		printf("%d nodes generated\n", generated);
		printf("%d nodes expanded\n", expanded);
	}
}
