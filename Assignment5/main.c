#include "functions.h"

int main(int argc, char **argv){
	char a;
	int j, x, i = 1;
	int scanned_clauses = 0;
	bool result;
	m = 99999;
		
	//scan the input
	while(getchar() == 'c')
		throwLine();
	
	initializeCNF();
	while(scanned_clauses < m){		
		scanClause(i);
		i++;
		scanned_clauses++;
	}
	
	/*printf("N: %d, M: %d\n", n, m);
	printf("CLAUSES\n");
	for(i = 1; i <= m; i++){
		printf("Clause %d, pointer %p : ", i, (void*)&clauses[i]);
		for(j = 1; j <= n; j++)
			printf("%d ", clauses[i].literals[j]);
		printf("\n");
	}
	
	printf("VARIABLES\n");
	list l;
	for(i = 1; i <= n; i++){
		printf("Variable %d\n", i);
		printf("Positive : ");
		for(l = (variables[i].posOccList) -> next; l != NULL; l = l -> next)
			printf("%p ", (void*)l -> clause);
		printf("\n");
		
		printf("Negative : ");
		for(l = (variables[i].negOccList) -> next; l != NULL; l = l -> next)
			printf("%p ", (void*)l -> clause);
		printf("\n");
	}
	printf("******************************************************\n");*/

	nodes = 0;
	top_stack = 0;
	
	result = DLL();
	
	//prints the output
	printOutput(result);
	
	printf("%d branching nodes explored.\n", nodes);
	
	
	return 0;
}

