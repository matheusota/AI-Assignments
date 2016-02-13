#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//string type
typedef char string[100];
 
//structure to represent a predicate
typedef struct predicate_aux{
	string label;
	int n_var;
	string variables[50];
} predicate;

//structure to represent an action
typedef struct action_aux{
	string label;
	int n_var;
	string variables[50];
	int n_pre, n_preNeg, n_add, n_del;
	predicate pre[50];
	predicate preNeg[50];
	predicate add[50];
	predicate del[50];
} action;

//structure to represent a tree node
//by default all predicates are false, the only ones that are not false are the ones in the state
typedef struct node_aux{
	string act;
	predicate predicates[100];
	int n_predicates, n_childs;
	struct node_aux *childs[1000];
	struct node_aux *parent;
} node, *tree;

//structure of a element of the queue
typedef struct queue_aux{
	int g;
	float h;
	tree t;
} queue_vector;

//global variables
int n_moves; //total number of moves

string constants[100]; //structure to hold each constant
int n_constants;

action actions[1000]; //structure to hold all the actions
int n_actions;

action groundedActions[1000]; //structure to hold all the grounded actions
int n_groundedActions;

string hash_key[100], hash_result[100]; //hash to associate for each variable a constant
int n_hash;

tree initial, goal; //initial and goal states

queue_vector queue[10000]; //queue structure
int n_queue;

string output[1000]; //holds the actions to be printed to the output
int n_output;
	
predicate goalPredicatesNeg[100]; //negated predicates of the goal
int n_goalPredicatesNeg;

float w; //weigh for the weighted A*

int expanded; //number of nodes expanded
int generated; //number of nodes generated

//reading functions
void ignoreComments();
void readPredicates();
void readConstants();
void scanAction();
void scanInitial();
void scanGoal();

//grounding functions
int findHash(string variable);
char* possibleCombinations(string current, int x, bool added[]);
char*** translateCombinations(string combinations, int *k);
bool isVariable(string s);
void groundAction(int index);

//queue functions
void insertQueue(tree t, int g, float h);
void removeQueue(tree *t, int *g, float *h);
void orderQueue();

//planning functions
bool comparePredicates(predicate a, predicate b);
bool checkPreconditions(tree s, action a);
tree applyAction(tree s, action a);
bool comparePredicates(predicate a, predicate b);
bool isGoal(tree s);
int checkDuplicate(tree t, tree child);
int countUnachieved(tree s);
tree astar(int x);

//debug function
void printPredicate(predicate p);
char* printAction(action a);
