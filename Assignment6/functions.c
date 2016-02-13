#include "functions.h"

//associate a tree with a variable
void treeToVar(tree t, char *string){
	int i;
	
	for(i = 0; i < n_vars; i++){
		if(strcmp(variables[i].string, string) == 0)
			variables[i].t = t;
	}
}

//return the index of a variable
int findVar(char *string){
	int i;
	
	for(i = 0; i < n_vars; i++){
		if(strcmp(variables[i].string, string) == 0)
			return i;
	}
	
	return -1;
}

//clean the trees on the variables array
void cleanVar(){
	int i;
	
	for(i = 0; i < n_vars; i++)
		variables[i].t = NULL;
}

// remove spaces from a string
void removeSpaces(char *string)
{
	int i, count = 0;
    
    for(i = 0; string[i] != '\0'; i++){
        if (string[i] != ' '){
			string[count] = string[i];
            count++;
		}
	}
	
    string[count] = '\0';
}

//check if label is a function
bool isFunction(char *string)
{
	if(string[0] == '*')
		return true;
	else
		return false;
}

//check if label is a variable
bool isVariable(char *string)
{
	if(string[0] > 96 && string[0] < 123)
		return true;
	else
		return false;
}

// find the end of a term in the term list
int findEndTerm(char *string){
	int i, open_p = 0; //number of opened parenthesis
	
	for(i = 0; string[i] != '\0'; i++){
		if(string[i] == ',' && open_p == 0)
			return i;
		
		//opened a parenthesis
		else if(string[i] == '(')
			open_p++;
		//closed a parenthesis
		else if(string[i] == ')')
			open_p--;
	}
	
	return i;
}

//insert child node on the tree
tree insertChild(tree t, char *string, int size, bool predicate){
	tree child = malloc(sizeof(tree_node));
	char string_aux[1000] = "*";
	
	//set the child as son of t, set number of childs to 0 
	t -> childs[t -> n_childs] = child;
	t -> n_childs++;
	child -> n_childs = 0;
	child -> parent = t;
	
	//writes the label of the node, functions starts with *
	if(predicate){
		size++;
		strcat(string_aux, string);
	}
	else
		strcpy(string_aux, string);
	strncpy(child -> label, string_aux, size);
	
	return child; 
}

//search for a label on the tree
bool findLabel(tree t, char *string){
	int i;
	bool founded = false;
	
	//see if there is already a tree associated with the label of the tree
	i = findVar(t -> label);
	if(i != -1 && variables[i].t != NULL)
		t = variables[i].t;
		
	if(strcmp(t -> label, string) == 0)
		return true;
	else{
		for(i = 0; (i < t -> n_childs) && !founded; i++)
			founded = founded || findLabel(t -> childs[i], string);
	}
	
	return founded;
}

//replace subtrees
void replaceTrees(tree t1, tree t2){
	tree parent = t1 -> parent;
	int i;
	
	for(i = 0; i < parent -> n_childs; i++){
		if(parent -> childs[i] == t1)
			break;
	}
	
	parent -> childs[i] = t2;
}

//check if a character is upper case
bool upperCase(char c){
	if(c > 64 && c < 91)
		return true;
	else
		return false;
}

//return the index of where the first open parenthesis is
int findParenthesis(char *string){
	int i;
	
	for(i = 0; i < strlen(string); i++){
		if(string[i] == '(')
			return i;
	}
	
	return -1;
}

void analyzePredicate(tree t, char *string, int tree_number){
	int p = findParenthesis(string);
	char aux_string[1000];
	tree child;

	//predicate or -predicate
	if((upperCase(string[0]) && p > 0) || (string[0] == '-' && upperCase(string[1]) && p > 1)){
		//insert on the tree
		child = insertChild(t, string, p, true);
		
		//copy term list to a temporary string
		strncpy(aux_string, &string[p+1], strlen(string) - p - 2);
		aux_string[strlen(string) - p - 2] = '\0';
		
		//analyze the term list
		analyzeTermList(child, aux_string, tree_number);
	}
	else
		printf("Invalid instruction %s\n", string);
}

void analyzeTermList(tree t, char *string, int tree_number){
	char aux_string[1000];
	char *final_position = &string[strlen(string)];
	int i;
	
	while(string < final_position){
		//find end of the term
		i = findEndTerm(string);
		
		//copy to a temporary string
		strncpy(aux_string, string, i);
		aux_string[i] = '\0';
		
		//analyze the term
		analyzeTerm(t, aux_string, tree_number);
		
		//get next term
		string = &string[i+1];
	}
}

void analyzeTerm(tree t, char *string, int tree_number){
	int p = findParenthesis(string);
	bool upper = upperCase(string[0]);
	tree child;
	int i;
	
	//capitalized function name
	if(p != -1 && upper)
		analyzePredicate(t, string, tree_number);
	
	//constant name or lowercase variable name
	else{
		//insert on the array if it is a variable
		if(isVariable(string)){
			//variables of second clause starts with ends with 2c
			if(tree_number == 1)
				strcat(string, "2c");
			
			i = findVar(string);
			
			//add to the variables array
			if(i == -1){
				strcpy(variables[n_vars].string, string);
				variables[n_vars].t = NULL;
				n_vars++;
			}
		}
		
		//insert on the tree
		insertChild(t, string, strlen(string), false);
	}
}

//print a tree in prefix order
void printTree(tree t){
	int i = findVar(t -> label);
	
	if(i != -1 && variables[i].t != NULL)
		printTree(variables[i].t);
	else
		printf("%s", t -> label[0] == '*' ? &t -> label[1] : t -> label);
	
	if(t -> n_childs > 0){
		printf("(");
		for(i = 0; i < t -> n_childs; i++){
			printTree(t -> childs[i]);
			
			if(i != t -> n_childs - 1)
				printf(", ");
		}
		printf(")");
	}
}

//print output of a line
void printOutput(int line){
	int i;
	
	for(i = 0; i < preds_lines[line]; i++){
		if(negative[line][i])
			printf("-");	
		printTree(predicates[line][i] -> childs[0]);
		
		if(i != preds_lines[line] - 1)
			printf(" | ");
	}
	printf("\n");
}
