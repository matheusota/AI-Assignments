#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//structure representing tree node
typedef struct tree_node_aux{
	char label[1000];
	int n_childs;
	struct tree_node_aux* parent;
	struct tree_node_aux* childs[100];
} tree_node, *tree;

//structure to associate each variable with a tree
typedef struct variable_aux{
	char string[1000];
	tree t;
} variable;

//global variables
char token[1000];
tree predicates[1000][1000]; //store each predicate
bool negative[1000][1000]; //flags to know the polarity of the sentence
int preds_lines[1000]; //number of predicates in the line
variable variables[1000]; //array to put every variable founded
int n_vars; //number of variables
int n_lines; //number of lines

//general functions
void treeToVar(tree t, char *string);
int findVar(char *string);
void cleanVar();
void removeSpaces(char *string);
bool isFunction(char *string);
bool isVariable(char *string);
int findEndTerm(char *string);
tree insertChild(tree t, char *string, int size, bool predicate);
bool findLabel(tree t, char *string);
void replaceTrees(tree t1, tree t2);
bool upperCase(char c);
int findParenthesis(char *string);
void analyzePredicate(tree t, char *string, int tree_number);
void analyzeTermList(tree t, char *string, int tree_number);
void analyzeTerm(tree t, char *string, int tree_number);
void printTree(tree t);
void printOutput(int line);
bool unifier(tree t1, tree t2);
