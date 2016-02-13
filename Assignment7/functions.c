#include "functions.h"

// ------------------------ Analysing Functions -------------------------------
void analyzePredicate(tree root, tree t, char *string, int axiom_id){
	int p = findParenthesis(string);
	char aux_string[1000];
	tree child;
	bool negative;
	
	//predicate or -predicate
	if((upperCase(string[0]) && p > 0) || (string[0] == '-' && upperCase(string[1]) && p > 1)){
		//check polarity
		if(string[0] == '-'){
			negative = true;
			string = &string[1];
			p--;
		}
		else
			negative = false;
			
		//insert on the tree
		child = insertChild(t, string, p, negative, true, axiom_id);
		
		//insert on the index list if the tree is not the query
		if(axiom_id != -1)
			insertIndexTerm(child -> label, root);
		
		//copy term list to a temporary string
		strncpy(aux_string, &string[p+1], strlen(string) - p - 2);
		aux_string[strlen(string) - p - 2] = '\0';
		
		//analyze the term list
		analyzeTermList(root, child, aux_string, axiom_id);
	}
	else
		printf("Invalid instruction %s\n", string);
}

void analyzeTermList(tree root, tree t, char *string, int axiom_id){
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
		analyzeTerm(root, t, aux_string, axiom_id);
		
		//get next term
		string = &string[i+1];
	}
}

void analyzeTerm(tree root, tree t, char *string, int axiom_id){
	int p = findParenthesis(string);
	bool negative, upper = upperCase(string[0]);
	tree child;
	int i;
	char aux[10];
	
	//capitalized function name
	if(p != -1 && upper)
		analyzePredicate(root, t, string, axiom_id);
	
	//constant name or lowercase variable name
	else{
		//insert on the array if it is a variable
		if(isVariable(string)){
			//the variables on each clause ends with (#clause)c
			/*sprintf(aux, "%dc", axiom_id);
			strcat(string, aux);*/
			
			i = findVar(string);
			
			//add to the variables array
			if(i == -1){
				strcpy(variables[n_vars].string, string);
				variables[n_vars].t = NULL;
				n_vars++;
			}
		}
		
		//check polarity
		if(string[0] == '-'){
			negative = true;
			string = &string[1];
		}
		else
			negative = false;
		
		//insert on the tree
		child = insertChild(t, string, strlen(string), negative, false, axiom_id);
		
		//if is a constant and the tree is not the query, insert on the index list
		/*if(upper && axiom_id != -1)
			insertIndexTerm(child -> label, root);*/
	}
}

// ------------------------ Tree Functions -------------------------------

//insert child node on the tree
tree insertChild(tree t, char *string, int size, bool negative, bool predicate, int axiom_id){
	tree child = malloc(sizeof(tree_node));
	char string_aux[1000] = "*";
	
	//set the child as son of t, set number of childs to 0 
	t -> childs[t -> n_childs] = child;
	t -> n_childs++;
	child -> n_childs = 0;
	child -> parent = t;
	child -> negative = negative;
	child -> axiom_id = axiom_id;
	
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

//associate a tree with a variable
void treeToVar(tree t, char *string){
	int i;
	
	for(i = 0; i < n_vars; i++){
		if(strcmp(variables[i].string, string) == 0)
			variables[i].t = t;
	}
}

//search for a label on the tree
tree findLabel(tree t, char *string){
	int i;
	tree result = NULL;
	
	//see if there is already a tree associated with the label of the tree
	i = findVar(t -> label);
	if(i != -1 && variables[i].t != NULL)
		result = variables[i].t;
	
	//search the tree
	if(strcmp(t -> label, string) == 0)
		return t;
	else{
		for(i = 0; (i < t -> n_childs) && t == NULL; i++)
			result = findLabel(t -> childs[i], string);
	}
	
	return result;
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

//put on an array the nodes that are predicates
void listNodes(tree t){
	int i;
	
	if(t != NULL && ((t -> label)[0] == '*' || (t -> label)[0] == '@')){
		if((t -> label)[0] != '@'){
			strcpy(nodesListed[n_nodes_listed], t -> label);
			n_nodes_listed++;
		}
		
		for(i = 0; i < t -> n_childs; i++)
			listNodes(t -> childs[i]);
	}
}


//Copy a tree
tree copyTree(tree t, tree parent){
	int i = findVar(t -> label);
	tree new;
	
	//check if it is already in the list of variables
	if(i != -1 && variables[i].t != NULL)
		t = variables[i].t;
	
	//copy the tree
	if(t != NULL){
		new = malloc(sizeof(tree_node));
		strcpy(new -> label, t -> label);
		new -> negative = t -> negative;
		new -> n_childs = t -> n_childs;
		new -> axiom_id = t -> axiom_id;
		new -> parent = parent;
		
		for(i = 0; i < t -> n_childs; i++)
			new -> childs[i] = copyTree(t -> childs[i], new);
		
		return new;
	}
	else
		return NULL;
}

//compare two trees
bool compareTrees(tree t1, tree t2){
	int i;
	bool result = false;

	//check if a subtree was already assigned to a variable in the trees
	i = findVar(t1 -> label);
	if(i != -1 && variables[i].t != NULL)
		t1 = variables[i].t;
		
	i = findVar(t2 -> label);
	if(i != -1 && variables[i].t != NULL)
		t2 = variables[i].t;
	
	//compare both trees	
	if(strcmp(t1 -> label, t2 -> label) == 0 && t1 -> n_childs == t2 -> n_childs && t1 -> negative == t2 -> negative){
		for(i = 0; i < t1 -> n_childs; i++){
			if(!compareTrees(t1 -> childs[i], t2 -> childs[i]))
				return false;
		}
		result = true;
	}
	
	return result;
}

// ------------------------ Utility Functions -------------------------------

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

//check if a tree is already in the axioms
bool alreadyAnAxiom(tree t){
	int i;
	
	for(i = 0; i < n_axioms; i++){
		if(compareTrees(axioms[i], t))
			return true;
	}
	
	return false;
}
// --------------------- Build Indexes Functions -------------------------------

//insert a term in the index list
void insertIndexTerm(char *label, tree t){
	int i;
	
	for(i = 0; i < n_terms; i++){
		//the term is already on the list
		if(strcmp(termlist[i].label, label) == 0){
			termlist[i].pointers[termlist[i].n_pointers] = t;
			termlist[i].n_pointers++;
			break;
		}
	}
	
	//the term wasn't on the list, add it
	if(i == n_terms){
		strcpy(termlist[i].label, label);
		termlist[i].pointers[0] = t;
		termlist[i].n_pointers++;
		n_terms++;
	}
}

//get index of the position in the termlist array
int findTermList(char *label){
	int i;
	
	for(i = 0; i < n_terms; i++){
		if(strcmp(label, termlist[i].label) == 0)
			return i;
	}
	
	return -1;
}


//remove from the query array and insert the result into the axioms
void removeQueryInsertAxiom(int m){
	int i;
	tree t;
	char *aux[1000];
	
	//insert into the axioms
	t = query[m];
	axioms[n_axioms] = t;
	
	for(i = m; i < n_query - 1; i++)
		query[i] = query[i + 1];
		
	n_query--;
	n_axioms++;
}

// --------------------- Output Functions -------------------------------

//print a tree in prefix order
void printTree(tree t){
	int i = findVar(t -> label);
	
	if(i != -1 && variables[i].t != NULL)
		printTree(variables[i].t);
	else{
		if(t -> negative)
			printf("-");
		
		printf("%s", t -> label[0] == '*' ? &t -> label[1] : t -> label);
	}
	
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
	
	printf("%d: ", line + 1);
	
	for(i = 0; i < axioms[line] -> n_childs; i++){	
		printTree(axioms[line] -> childs[i] -> childs[0]);
		
		if(i != axioms[line] -> n_childs - 1)
			printf(" | ");
	}
	printf("\n");
}

//print output of a resolution step
void printOutputResolution(tree t, tree_output parent, int axiom_id1, int axiom_id2, int axiom_id, bool done){
	int i;
	char aux[1000];
	
	if(parent != NULL)
		printf("%d and %d give %d: ", axiom_id1 + 1, axiom_id2 + 1, axiom_id + 1);
	else
		printf("%d: ", axiom_id);
	
	if(done)
		printf("<empty>\n");
	else{
		for(i = 0; i < t -> n_childs; i++){	
			printTree(t -> childs[i] -> childs[0]);
			
			if(i != t -> n_childs - 1)
				printf(" | ");
		}
		printf("\n");
	}
}


//insert a node in the output tree
tree_output insertOutputNode(tree t, tree_output parent, int axiom_id1, int axiom_id2, int axiom_id, bool done){
	tree_output new;
	
	new = malloc(sizeof(output_node));
	
	new -> axiom_id = axiom_id;
	new -> axiom_id1 = axiom_id1;
	new -> axiom_id2 = axiom_id2;
	new -> parent = parent;
	new -> t = t;
	new -> n_pointers = 0;
	new -> done = done;
	
	return new;
}

//get next output node
void getNextOut(){
	int i;
	
	treeOut = nextOut[0];
	
	for(i = 1; i < n_out; i++)
		nextOut[i -1] = nextOut[i];
	
	n_out--;
}

//traverse up the output tree
void traverseOutput(){
	int i = 0;
	
	while(treeOut != NULL){
		nextOut[i] = treeOut;
		treeOut = treeOut -> parent;
		i++;
	}
	
	n_out = i;
}
