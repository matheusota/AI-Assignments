#include "functions.h"

//throw away a line of commentary
void throwLine(){
	char a = 'a';
	
	while(a != '\n')
		a = getchar();
}

//scan the number of variables and the number of clauses and initialize the structure
void initializeCNF(){
	int i,j;
	
	//throw away string " cnf "
	for(i = 0; i < 5; i++)
		getchar();
		
	//scan cnf dimensions
	scanf("%d %d", &n, &m);
	
	//initialize clauses
	for(i = 1; i <= m; i++){
		clauses[i].index = i;
		clauses[i].pos = 0;
		clauses[i].neg = 0;
		clauses[i].subsumedBy = 0;
		
		for(j = 0; j < n; j++)
			clauses[i].literals[j] = 0;
	}
	
	//creates a head in the lists
	for(i = 1; i <= n; i++){
		variables[i].posOccList = malloc(sizeof(list_node));
		variables[i].posOccList -> next = NULL;
		
		variables[i].negOccList = malloc(sizeof(list_node));
		variables[i].negOccList -> next = NULL;
	}
}

//insert in a liked list, l is the head
void insertList(list l, clauseType *c){
	list aux = l -> next;
	list new;
	
	new = malloc(sizeof(list_node));
	new -> clause = c;
	new -> next = aux;
	l -> next = new;
}

//scan the variables and add them to the clause i
void scanClause(int i){
	int x = 1;
	
	while(x != 0){
		//scan the variable
		scanf("%d", &x);
		
		//update the structures
		if(x != 0){
			variables[x].state = 0;
			
			if(x > 0){
				clauses[i].pos++;
				clauses[i].literals[x] = 1;
				variables[x].nrPosOcc++;
				insertList(variables[x].posOccList, &clauses[i]);
			}
			else{
				clauses[i].neg++;
				clauses[i].literals[-x] = -1;
				variables[-x].nrNegOcc++;
				insertList(variables[-x].negOccList, &clauses[i]);
			}
		}
	}
}

//print the output in the DIMACS format
void printOutput(bool result){
	int i;
	
	printf("s cnf %d %d %d\n", result ? 1 : 0, n, m);
	
	if(result){
		for(i = 1; i <= n; i++){
			if(variables[i].state != 0)
				printf("v %d\n", variables[i].state * i);
			else
				printf("v %d\n", i);
		}
	}
}

//add to the stack
void push(int x){
	stack[top_stack] = x;
	top_stack++;
}

//pop from the stack
int pop(){
	top_stack--;
	return stack[top_stack];
}
