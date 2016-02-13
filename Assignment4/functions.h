#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//structure of each edge in adjacency list
typedef struct adj_list_aux{
	int index;
	struct adj_list_aux *next;
} adj_list_node, *adj_list;

//structre of each vertex in the adjacency list
typedef struct vertex_aux{
	int color;
	int restrictions[1000];//vector representing the possible colors for the vertex
	int size;//number of colors available
	adj_list head;
} vertex;

//global variables
int n, m, k, nodes;
vertex graph[10000];

//functions to read and process the input
void startsGraph();
void addEdge(int v1, int v2);
void throwLine();
void scanDimensions();
void scanEdge();
void printList(int i);
void printOutput();

//graph coloring functions
bool checkVertices(int u);
int findValue(int mode);
bool dfs(int u, int color, int n_color, int mode);



