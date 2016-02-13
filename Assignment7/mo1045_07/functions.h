#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//structure representing tree node
typedef struct tree_node_aux{
	char label[1000];
	bool negative;
	int n_childs;
	int axiom_id;
	struct tree_node_aux* parent;
	struct tree_node_aux* childs[100];
} tree_node, *tree;

//structure to associate each variable with a tree
typedef struct variable_aux{
	char string[1000];
	tree t;
} variable;

//structure to associate each term with pointers to where the term appears
typedef struct term_aux{
	char label[1000];
	tree pointers[1000];
	int n_pointers;
} term;

//tree structure to print answer
typedef struct tree_output_aux{
	tree t;
	int axiom_id1;
	int axiom_id2;
	int axiom_id;
	bool done;
	struct tree_output_aux *parent;
	struct tree_output_aux *pointers[1000];
	int n_pointers;
}output_node, *tree_output;

//global variables
tree axioms[1000]; //store each axiom of the KB
int n_axioms;

variable variables[1000]; //array to put every variable founded
int n_vars;

term termlist[1000]; //array of terms to associate with where the term appears
int n_terms;

tree query[1000]; //query
int n_query;

char nodesListed[1000][1000];
int n_nodes_listed;

tree_output treeOut;
tree_output nextOut[1000];
int n_out;

int n_resolutions;

// ------------------------ Analysing Functions -------------------------------
void analyzePredicate(tree root, tree t, char *string, int axiom_id);
void analyzeTermList(tree root, tree t, char *string, int axiom_id);
void analyzeTerm(tree root, tree t, char *string, int axiom_id);

// ------------------------ Tree Functions -------------------------------
tree insertChild(tree t, char *string, int size, bool negative, bool predicate, int axiom_id);
void treeToVar(tree t, char *string);
tree findLabel(tree t, char *string);
void replaceTrees(tree t1, tree t2);
void listNodes(tree t);
tree copyTree(tree t, tree parent);
bool compareTrees(tree t1, tree t2);

// ------------------------ Utility Functions -------------------------------
int findVar(char *string);
void cleanVar();
void removeSpaces(char *string);
bool isFunction(char *string);
bool isVariable(char *string);
int findEndTerm(char *string);
bool upperCase(char c);
int findParenthesis(char *string);
bool alreadyAnAxiom(tree t);

// --------------------- Build Indexes Functions -------------------------------
void insertIndexTerm(char *label, tree t);
int findTermList(char *label);
void removeQueryInsertAxiom(int m);

// --------------------- Output Functions -------------------------------
void printTree(tree t);
void printOutput(int line);
void printOutputResolution(tree t, tree_output parent, int axiom_id1, int axiom_id2, int axiom_id, bool done);
tree_output insertOutputNode(tree t, tree_output parent, int axiom_id1, int axiom_id2, int axiom_id, bool done);
void getNextOut();
void traverseOutput();

bool unifier(tree t1, tree t2);
bool queryUnify();
tree resolution(tree t1, tree t2, tree model, int axiom_id);
