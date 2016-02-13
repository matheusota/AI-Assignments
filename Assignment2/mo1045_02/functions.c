#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

//insert on front of the list
void insertList(char a){
	list new;
	
	new = malloc(sizeof(list_node));
	if(new == NULL)
		printf("error alocating memory for list node\n");
	new -> next = actions;
	new -> action = a;
	
	actions = new;
}

//insert on front of the dirts list
void insertListDirt(int x, int y){
	list_dirt new;
	
	new = malloc(sizeof(list_node_dirt));
	if(new == NULL)
		printf("error alocating memory for dirt node\n");
	new -> next = dirts;
	new -> x = x;
	new -> y = y;
	
	dirts = new;
}

//removes from the dirt list
void removeListDirt(int x, int y){
	list_dirt aux;
	
	if(dirts != NULL){
		//checks first node
		if(dirts -> x == x && dirts -> y == y)
			dirts = dirts -> next;
		
		//checks the rest of the list
		else{
			for(aux = dirts; aux -> next != NULL; aux = aux -> next){
				if(aux -> next -> x == x && aux -> next -> y == y)
					aux -> next = aux -> next -> next;
					break;
			}
		}
	}
}

//prints a list
void printList(){
	list aux = actions;
		
	while(aux != NULL){
		printf("%c\n", aux -> action);
		aux = aux -> next;
	}
}

//insert in the end of the queue
void insertQueue(tree t, double f){
	queue[n_queue].t = t;
	queue[n_queue].f = f;
	
	n_queue++;
}

//remove the first element from the queue
void removeQueue(tree *t, double *f){
	int i;
	
	*t = queue[0].t;
	*f = queue[0].f;
	//shift the elements
	for(i = 0; i < n_queue; i++){
		queue[i].t = queue[i+1].t;
		queue[i].f = queue[i+1].f;
	
	}
	
	n_queue--;
}

//creates a new matrix
char** newMatrix(){
	int i;
	char **mat;
	
	mat = (char **)malloc(n * sizeof(char*));
	if(mat == NULL)
		printf("error allocating memory for a matrix\n");
	for(i = 0; i < n; i++){ 
		mat[i] = (char *)malloc(m * sizeof(char));
		if(mat[i] == NULL)
			printf("error allocating memory for a matrix\n");
	}
	
	return mat;
}

//prints a matrix
void printMatrix(char **mat){
	int i, j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			printf("%c ", mat[i][j]);
		printf("\n");
	}
}

//free the space of a matrix
void freeMatrix(char **mat){
	int i;
	for (i = 0; i < n; i++)
		free(mat[i]);
	
	free(mat);
}

//copy one matrix to another
void copyMatrix(char** from, char** to){
	int i, j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++) 
			to[i][j] = from[i][j];
	}
}

//compare matrices
int compareMatrix(char** m1, char** m2){
	int i, j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			if(m1[i][j] != m2[i][j])
				return 0;
		}
	}
	
	return 1;
}

//Knuth multiplicative method
uint32_t int_hash(uint32_t v)
{
    return v * UINT32_C(2654435761);
}

//hash function to map the position of the robot
long hashFunction(int x, int y){
	return (51 + int_hash(y)) * 51 + int_hash(x);
}

//insert a node in the tree
tree insertTree(tree p, int dirt, int x, int y, char** mat, char a, int level){
	tree new;
	int i;
	
	new = malloc(sizeof(tree_node));
	if(new == NULL)
		printf("error allocating memory for tree\n");
	new -> parent = p;
	new -> dirt = dirt;
	new -> x = x;
	new -> y = y;
	new -> mat = mat;
	new -> action = a;
	new -> level = level;
	new -> N = NULL;
	new -> S = NULL;
	new -> W = NULL;
	new -> E = NULL;
	new -> hashId = hashFunction(x, y);
	
	return new;
}

//free a tree
void freeTree(tree t){
	if(t != NULL){
		freeTree(t -> N);
		freeTree(t -> S);
		freeTree(t -> E);
		freeTree(t -> W);
		freeMatrix(t -> mat);
		free(t);
	}
}

//checks if it find a duplicate state
int checkDuplicate(tree t, char** mat, long hashId, int dirt){
	tree new;
	
	if(t != NULL){
		if(hashId == t -> hashId && dirt == t -> dirt && compareMatrix(mat, t -> mat) == 1)
			return 1;
		else{
			return (checkDuplicate(t -> N, mat, hashId, dirt) == 1) || (checkDuplicate(t -> S, mat, hashId, dirt) == 1)
			|| (checkDuplicate(t -> W, mat, hashId, dirt) == 1) || (checkDuplicate(t -> E, mat, hashId, dirt) == 1);
		}
	}
	
	return 0;
}

//order queue  according to f value
void orderQueue(){
	int i, j;
	queue_vector a;
	
	for(i = 0; i < n_queue; i++){
        for(j = i + 1; j < n_queue; j++){
            if(queue[i].f > queue[j].f){
                a.f = queue[i].f;
                a.t = queue[i].t;
                queue[i].f = queue[j].f;
                queue[i].t = queue[j].t;
                queue[j].f = a.f;
                queue[j].t = a.t;
            }
        }
    }
}

//compute manhattan distance of 2 points
double manhattan(int x1, int y1, int x2, int y2){
	return abs(x1-x2) + abs(y1-y2);
}

//compute euclidean distance of 2 points
double euclidean(int x1, int y1, int x2, int y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

//compute distances(manhattan if h2 and euclidean if h1) to all dirts, return the smaller
double computeDistancesDirts(int x, int y, int heuristic){
	double smaller, d;
	list_dirt aux;
	
	smaller = 0;
	
	if(dirts != NULL){
		if(heuristic == 1)
			smaller = euclidean(x, y, dirts -> x, dirts -> y);
		else
			smaller = manhattan(x, y, dirts -> x, dirts -> y);
			
		for(aux = dirts -> next; aux != NULL; aux = aux -> next){
			if(heuristic == 1){
				d = euclidean(x, y, aux -> x, aux -> y);
				
				if(d < smaller)
					smaller = d;
			}
			else{
				d = manhattan(x, y, aux -> x, aux -> y);
				
				if(d < smaller)
					smaller = d;
			}
		}
	}
	
	return smaller;
}

//compute the f = g + h function according to the heuristic
double computeHeuristic(int x, int y, int g, int heuristic){
	//h0
	if (heuristic == 0)
		return g;
	
	//h1 or h2
	else
		return computeDistancesDirts(x, y, heuristic) + g;
}
