#include <stdint.h>

//structure of the list of actions taken
typedef struct list_aux{
	char action;
	struct list_aux *next;
} list_node, *list;

//structure of a list of dirt
typedef struct list_aux_dirt{
	int x;
	int y;
	struct list_aux_dirt *next;
} list_node_dirt, *list_dirt;

//structure of each node in a tree
typedef struct tree_aux{
	long int hashId;
	struct tree_aux *parent;
	struct tree_aux *N;
	struct tree_aux *S;
	struct tree_aux *W;
	struct tree_aux *E;
	char action;
	int dirt;
	int x;
	int y;
	int level;
	char **mat;
	
} tree_node, *tree;

//structure of a element of the queue
typedef struct queue_aux{
	double f;
	tree t;
} queue_vector;

//global variables
int n, m, n_queue;
int generated, expanded;
char w[1000][1000];
list actions;
queue_vector queue[1000000];
list_dirt dirts;

//functions declaration
void insertList(char a);
void insertListDirt(int x, int y);
void printList();

void insertQueue(tree t, double f);
void removeQueue(tree *t, double *f);
void orderQueue();

char** newMatrix();
void freeMatrix(char **mat);
void copyMatrix(char** from, char** to);
int compareMatrix(char** m1, char** m2);

tree insertTree(tree p, int dirt, int x, int y, char** mat, char a, int level);
void freeTree(tree t);
int checkDuplicate(tree t, char** mat, long hashId, int dirt);
long hashFunction(int x, int y);
uint32_t int_hash(uint32_t v);

int dfs(int x, int y, int dirt, int level, int limit);

double computeHeuristic(int x, int y, int g, int heuristic);
double computeDistancesDirts(int x, int y, int heuristic);
double euclidean(int x1, int y1, int x2, int y2);
double manhattan(int x1, int y1, int x2, int y2);

tree astar(int x, int y, int d, int heuristic);
void printAstar(int x, int y, int dirt, int heuristic);

