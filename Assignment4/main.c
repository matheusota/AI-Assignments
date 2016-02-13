#include "functions.h"

int main(int argc, char **argv){
	int i, scanned_edges = 0;
	char a;
	bool result;
	m = 99999;
	
	//get the number of colors to try
	k = atoi(argv[2]);
		
	//scan the input
	while(scanned_edges < m){
		a = getchar();
		
		if(a == 'p')
			scanDimensions();
		else if(a == 'e'){
			scanEdge();
			scanned_edges++;
		}
		
		throwLine();
	}
	
	/*
	//print graph
	printf("READED GRAPH:\n");
	for(i = 0; i < n; i++){
		printf("VERTEX: %d -> ", i);
		printList(i);
	}*/
	
	nodes = 0;
	
	//runs the algorithm for each argument
	if(strcmp(argv[1], "dfs") == 0)
		result = dfs(0, 0, 0, 0);
	else if(strcmp(argv[1], "fc") == 0)
		result = dfs(0, 0, 0, 1);
	else if(strcmp(argv[1], "mcv") == 0)
		result = dfs(0, 0, 0, 2);
	
	//prints the output
	if(result)
		printOutput();
	else
		printf("No solution.\n");
	
	printf("%d branching nodes explored.\n", nodes);
	return 0;
}

