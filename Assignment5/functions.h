#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//structure representing each clause
typedef struct clause_aux{
	int index;
	int pos; //number of positive literals in the clause
	int neg; //number of negative literals in the clause
	int literals[1000]; //literals in the clause 
	int subsumedBy; //the variable that concluded that the clause is true
} clauseType;

//linked list for the pointers to the clauses
typedef struct list_aux{
	clauseType *clause;
	struct list_aux *next;
} list_node, *list;

//structure representing each variable
typedef struct variable_aux{
	int state; //-1 is open, 0 and 1 is the bit value
	int nrPosOcc; //number of positive occurrences
	int nrNegOcc; //number of negative occurrences
	list posOccList; //pointers to clauses of positive occurence
	list negOccList; //pointer to clauses of negative occurence 
} variableType;

//global variables
int n, m; //dimensions
clauseType clauses[10001]; //array of clauses
variableType variables[10001]; //array of variables
int stack[100000]; //stack used for backtracking
int top_stack; //top of the stack
int nodes; //number of nodes generated

//functions to read and process the input
void throwLine();
void initializeCNF();
void insertList(list l, clauseType *c);
void scanClause();
void printOutput(bool result);

//stack functions
void push(int x);
int pop();

//DLL implementation functions
void setVariable(int x);
void reverseSetVariable(int x);
void unitPropagate(int *propagate_stack);
bool DLL();
