#include "functions.h"

//start adjacency list structure of the graph
void startsGraph(){
	int i;
	
	for(i = 0; i < n; i++){
		graph[i].head = malloc(sizeof(adj_list_node));
		graph[i].head -> next = NULL;
		graph[i].color = -1;//no color
		graph[i].size = k;
	}
}

//inserts a vertex in the end of an adjacency list
void addEdge(int v1, int v2){
	adj_list aux = graph[v1].head;
	adj_list new;
	int i;
	
	new = malloc(sizeof(adj_list_node));
	new -> next = NULL;
	new -> index = v2;
	
	//initially all colors are possible
	for(i = 0; i < k; i++)
		graph[v2].restrictions[i] = 0;
		
	while(aux -> next != NULL)
		aux = aux -> next;
	
	aux -> next = new;
}


//throw away a line of commentary
void throwLine(){
	char a = 'a';
	
	while(a != '\n')
		a = getchar();
}

//scan the dimensions of the graph and create it
void scanDimensions(){
	int i;
	
	//throw away string " edge "
	for(i = 0; i < 6; i++)
		getchar();
		
	//scan graph dimensions
	scanf("%d %d", &n, &m);
	
	//creates a graph
	startsGraph();
}

//scan the edge of the graph and add it
void scanEdge(){
	int x, y;
	
	scanf("%d %d", &x, &y);
	addEdge(x-1, y-1);
	addEdge(y-1, x-1);//undirected graph
}

//auxiliary function to print a adjacency list
//funcao auxiliar que imprime uma lista de adjacencia
void printList(int i){
	adj_list aux = graph[i].head -> next;
	
	while(aux != NULL){
		printf("%d ", aux -> index);
		aux = aux -> next;
	}
	printf("\n");
}

//print the output in the DIMACS format
void printOutput(){
	int i;
	
	printf("s col %d\n", k);
	
	for(i = 0; i < n; i++)
		printf("l %d %d\n", i + 1, graph[i].color + 1);
}
