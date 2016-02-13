#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure of the list of actions taken
typedef struct list_aux{
	char action;
	struct list_aux *next;
} list_node, *list;

//structure of each node in a tree
typedef struct tree_aux{
	struct tree_aux *parent;
	struct tree_aux *N;
	struct tree_aux *S;
	struct tree_aux *W;
	struct tree_aux *E;
	char action;
	int dirt;
	int x;
	int y;
	char **mat;
	
} tree_node, *tree;

//global variables
int n, m, n_queue;
int generated, expanded;
char w[1000][1000];
list actions;
tree queue[1000000];

//insert on front of the list
void insertList(char a){
	list new;
	
	new = malloc(sizeof(list_node));
	new -> next = actions;
	new -> action = a;
	
	actions = new;
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
void insertQueue(tree t){
	queue[n_queue] = t;
	
	n_queue++;
}

//remove the first element from the queue
tree removeQueue(){
	tree t;
	int i;
	
	t = queue[0];
	
	//shift the elements
	for(i = 0; i < n_queue; i++)
		queue[i] = queue[i+1];
	
	n_queue--;
	
	return t;
}

//creates a new matrix
char** newMatrix(){
	int i;
	char **mat;
	
	mat = (char **)malloc(n * sizeof(char*));
	for(i = 0; i < n; i++) 
		mat[i] = (char *)malloc(m * sizeof(char));
	
	return mat;
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

//insert a node in the tree
tree insertTree(tree p, int dirt, int x, int y, char** mat, char a){
	tree new;
	int i;
	
	new = malloc(sizeof(tree_node));
	new -> parent = p;
	new -> dirt = dirt;
	new -> x = x;
	new -> y = y;
	new -> mat = mat;
	new -> action = a;
	
	return new;
}

//checks if it find a duplicate state
int checkDuplicate(tree t, char** mat){
	tree new;
	
	while(t != NULL){
		if(compareMatrix(mat, t -> mat) == 0){
			return (checkDuplicate(t -> N, mat) == 1) || (checkDuplicate(t -> S, mat) == 1)
			|| (checkDuplicate(t -> W, mat) == 1) || (checkDuplicate(t -> E, mat) == 1);
		}
		else
			return 1;
	}
	
	return 0;
}

/*executes depth first search on the world to find the plan to clean it
it returns 1 if founded a way to collect all dirt, else it returns 0*/
int dfs(int x, int y, int dirt){
	int instruction = 0; //0 -> U, 1 -> D, 2 -> L, 3 -> R
	int next_x, next_y;
	char temp = w[y][x];
	
	//increments the number of nodes expanded
	expanded++;
	
	//calculates the number of nodes that can be generated
	if(y != 0 && w[y-1][x] != '#' && w[y-1][x] != dirt + '0')
		generated++;
	if(y != n - 1 && w[y+1][x] != '#' && w[y+1][x] != dirt + '0')
		generated++;
	if(x != 0 && w[y][x-1] != '#' && w[y][x-1] != dirt + '0')
		generated++;
	if(x != m - 1 && w[y][x+1] != '#' && w[y][x+1] != dirt + '0')
		generated++;
	if(w[y][x] == '*')
		generated++;
	
	//vacuum the dirt
	if(w[y][x] == '*'){
		dirt--;
		expanded++;
		
		//check to see if it is the last one
		if(dirt == 0){
			insertList('V');
			return 1;
		}
	}
		
	//changes the cell value to the number of dirt left
	w[y][x] = dirt + '0';
	
	while(instruction < 4){
		//calculate the next cell to be seen acording to the instruction
		next_y = y;
		next_x = x;

		if(instruction == 0 && y != 0 && w[y-1][x] != '#')
			next_y = y - 1;
		else if(instruction == 1 && y != n - 1 && w[y+1][x] != '#')
			next_y = y + 1;
		else if(instruction == 2 && x != 0 && w[y][x-1] != '#')
			next_x = x - 1;
		else if(instruction == 3 && x != m - 1 && w[y][x+1] != '#')
			next_x = x + 1;
		
		//it just makes sense to pass through the same cell if the number of dirt left in the second time is different than the first	
		if((next_y != y || next_x != x) && w[next_y][next_x] != w[y][x]){
			if(dfs(next_x, next_y, dirt) == 1){
				if(instruction == 0)
					insertList('N');
				else if(instruction == 1)
					insertList('S');
				else if(instruction == 2)
					insertList('W');
				else if(instruction == 3)
					insertList('E');
				
				if(temp == '*')
					insertList('V');
					
				return 1;
			}
		}
		
			instruction++;
	}
	
	w[y][x] = temp;
	return 0;
}

/*implements djikstra(uniform-cost) algorithm, because the actions have all the same
weight, if you add each new action in the end of the queue the queue will be sorted
and this is just like bfs*/
tree djikstra(int x, int y, int d){
	char a = 'X';//X simbolize that no action was taken to get there
	tree t, t1, t2;
	char **mat1, **mat2;
	int i, j;
	
	//copy the starting matrix
	mat1 = newMatrix();
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++) 
			mat1[i][j] = w[i][j];
	}
	
	t1 = insertTree(NULL, d, x, y, mat1, a);
	t = t1;
	insertQueue(t1);
	
	while(n_queue > 0){
		//remove the first element of the queue
		t1 = removeQueue();
		
		d = t1 -> dirt;
		mat1 = t1 -> mat;
		a = t1 -> action;
		x = t1 -> x;
		y = t1 -> y;
		
		//check if there is no dirt left
		if(d == 0)
			return t1;
		
		//increments the number of nodes expanded
		expanded++;
		
		//adds into the queue
		if(y != 0 && mat1[y-1][x] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y-1][x];
			
			mat2[y-1][x] = '@';
			mat2[y][x] = '_';
			
			if(checkDuplicate(t, mat2) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*')
					t2 = insertTree(t1, d-1, x, y-1, mat2, 'n');
				else
					t2 = insertTree(t1, d, x, y-1, mat2, 'N');
					
				t1 -> N = t2;
					
				insertQueue(t2);
				generated++;
			}
		}
			
		if(y != n - 1 && mat1[y+1][x] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y+1][x];
			
			mat2[y+1][x] = '@';
			mat2[y][x] = '_';
			
			if(checkDuplicate(t, mat2) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*')
					t2 = insertTree(t1, d-1, x, y+1, mat2, 's');
				else
					t2 = insertTree(t1, d, x, y+1, mat2, 'S');
				
				t1 -> S = t2;
					
				insertQueue(t2);
				generated++;
			}
		}
		
		if(x != 0 && mat1[y][x-1] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y][x-1];
			
			mat2[y][x-1] = '@';
			mat2[y][x] = '_';
			
			if(checkDuplicate(t, mat2) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*')
					t2 = insertTree(t1, d-1, x-1, y, mat2, 'w');
				else
					t2 = insertTree(t1, d, x-1, y, mat2, 'W');
					
				t1 -> W = t2;
					
				insertQueue(t2);
				generated++;
			}
		}
		
		if(x != m - 1 && mat1[y][x+1] != '#'){
			mat2 = newMatrix();
			copyMatrix(mat1, mat2);
			
			a = mat1[y][x+1];
			
			mat2[y][x+1] = '@';
			mat2[y][x] = '_';
			
			if(checkDuplicate(t, mat2) == 0){
				//inserts in lowercase if there is dirt
				if(a == '*')
					t2 = insertTree(t1, d-1, x+1, y, mat2, 'e');
				else
					t2 = insertTree(t1, d, x+1, y, mat2, 'E');
					
				t1 -> E = t2;
					
				insertQueue(t2);
				generated++;
			}
		}
		
		//you could sort the queue here to match the djikstra algorithm showed in class,
		//but, like explained above, there is no need for this	
	}
	
	return NULL;
}

//prints the path of the djikstra algorithm
void printDjikstra(int x, int y, int dirt){
	tree t;
	
	if(dirt > 0){
		t = djikstra(x, y, dirt);

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
	
int main(int argc, char **argv){
	int i, j, a, dirt, x, y;
	dirt = 0;
	generated = 1;
	expanded = 0;
	
	//scan the size of the matrix
	scanf("%d %d", &m, &n);
	
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
			
			//counts the number of dirt
			if(w[i][j] == '*')
				dirt++;
		}
		
		//throw away break line
		a = getchar();
	}
	
	//executes dfs algorithm
	if(strcmp(argv[1], "depth-first") == 0){
		if(dirt > 0){
			if(dfs(x, y, dirt) == 1){
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
	
	//executes djikstra algorithm
	else if(strcmp(argv[1], "uniform-cost") == 0)
		printDjikstra(x, y, dirt);
	//unknown command
	else
		printf("command unknown\n");
	
	return 0;
}
