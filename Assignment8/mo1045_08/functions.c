#include "functions.h"

//READING FUNCTIONS---------------------------------------------------

//if is a commentary line, ignore it
void ignoreComments(){
	char a = getchar();
	
	while(a != '\n')
		a = getchar();
}

//read the predicates and put on the data structure
void readPredicates(){
	int i, index_label, index_var;
	char a;
	string label, var;
	bool openParenthesis  = false;
	
	//go to the first predicate
	for(i = 0; i < 11; i++)
		a = getchar();
	
	//scan all the line
	index_label = 0;
	
	while(a != '\n')
		a = getchar();
}

//read the constants and put on the data structure
void readConstants(){
	int i;
	char a;
	string constant;
	
	//go to the first constant
	for(i = 0; i < 10; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	i = 0;
	if(a != '\n'){
		while(true){
			if(a == ' ' || a == '\n'){
				//add temp string to the structure
				constant[i] = '\0';
				strcpy(constants[n_constants], constant);
				n_constants++;
				i = 0;
				
				if(a == '\n')
					break;
			}
			else{
				//add to the temp string
				constant[i] = a;
				i++;
			}
			
			a = getchar();
		}
	}
}

//scan an action
void scanAction(){
	action act;
	char a;
	string aux;
	int i = 0;
	bool openParenthesis;
	
	//intialize some parameters
	act.n_var = 0;
	act.n_pre = 0;
	act.n_preNeg = 0;
	act.n_del = 0;
	act.n_add = 0;
	
	//scan the label of the action
	scanf("%s ", act.label);
	
	//scan the arguments of the action
	a = getchar();
	if(a != '\n'){
		while(true){
			if(a == ' ' || a == '\n'){
				aux[i] = '\0';
				strcpy(act.variables[act.n_var], aux);
				act.n_var++;
				i = 0;
				
				if(a == '\n')
					break;
			}
			else{
				aux[i] = a;
				i++;
			}
			
			a = getchar();
		}
	}
	a = getchar();
	
	if(a == '#'){
		ignoreComments();
		getchar();
	}
	
	//scan the preconditions of the actions
	for(i = 0; i < 4; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	i = 0;	
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it to the preconditions
					aux[i] = '\0';
					strcpy(act.pre[act.n_pre].label, aux);
					act.pre[act.n_pre].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(act.pre[act.n_pre].variables[act.pre[act.n_pre].n_var], aux);
					act.pre[act.n_pre].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						act.n_pre++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
	
	a = getchar();
	if(a == '#'){
		ignoreComments();
		getchar();
	}
	
	//scan the negative preconditions of the actions
	for(i = 0; i < 7; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	i = 0;
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it to the neg preconditions
					aux[i] = '\0';
					strcpy(act.preNeg[act.n_preNeg].label, aux);
					act.preNeg[act.n_preNeg].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){					
					//add it to the structure
					aux[i] = '\0';
					strcpy(act.preNeg[act.n_preNeg].variables[act.preNeg[act.n_preNeg].n_var], aux);
					act.preNeg[act.n_preNeg].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						act.n_preNeg++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
	
	a = getchar();
	if(a == '#'){
		ignoreComments();
		getchar();
	}
	
	//scan the deletes of the actions
	for(i = 0; i < 4; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	i = 0;	
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it to the deletes
					aux[i] = '\0';
					strcpy(act.del[act.n_del].label, aux);
					act.del[act.n_del].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(act.del[act.n_del].variables[act.del[act.n_del].n_var], aux);
					act.del[act.n_del].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						act.n_del++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
			
	a = getchar();
	if(a == '#'){
		ignoreComments();
		getchar();
	}
	
	//scan the adds of the actions
	for(i = 0; i < 4; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	i = 0;	
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it to the adds
					aux[i] = '\0';
					strcpy(act.add[act.n_add].label, aux);
					act.add[act.n_add].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(act.add[act.n_add].variables[act.add[act.n_add].n_var], aux);
					act.add[act.n_add].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						act.n_add++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
	
	//copy structure
	actions[n_actions] = act;
	n_actions++;
}

//scan the initial state
void scanInitial(){
	int i;
	char a;
	bool openParenthesis = false;
	string aux;
	
	initial = malloc(sizeof(node));
	initial -> n_predicates = 0;
	initial -> n_childs = 0;
	initial -> parent = NULL;
	
	//go for the predicates
	for(i = 0; i < 8; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	//scan the predicates	
	i = 0;	
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it
					aux[i] = '\0';
					strcpy(initial -> predicates[initial -> n_predicates].label, aux);
					initial -> predicates[initial -> n_predicates].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(initial -> predicates[initial -> n_predicates].variables[initial -> predicates[initial -> n_predicates].n_var], aux);
					initial -> predicates[initial -> n_predicates].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						initial -> n_predicates++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
}

//scan the goal state
void scanGoal(){
	int i;
	char a;
	bool openParenthesis = false;
	string aux;
	
	goal = malloc(sizeof(node));
	goal -> n_predicates = 0;
	goal -> n_childs = 0;
	n_goalPredicatesNeg = 0;
	
	//go for the predicates
	for(i = 0; i < 5; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	//scan the predicates	
	i = 0;	
	while(a != '\n'){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it
					aux[i] = '\0';
					strcpy(goal -> predicates[goal -> n_predicates].label, aux);
					goal -> predicates[goal -> n_predicates].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(goal -> predicates[goal -> n_predicates].variables[goal -> predicates[goal -> n_predicates].n_var], aux);
					goal -> predicates[goal -> n_predicates].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						goal -> n_predicates++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
	
	//go for the negative predicates
	for(i = 0; i < 9; i++)
		a = getchar();
	
	if(a == ' ')
		a = getchar();
	
	//scan the negative predicates
	i = 0;
	while(a != '\n' && a != -1){
		//ignore spaces
		if(a != ' '){
			//read label
			if(!openParenthesis){
				if(a == '('){
					openParenthesis = true;
					
					//add it
					aux[i] = '\0';
					strcpy(goalPredicatesNeg[n_goalPredicatesNeg].label, aux);
					goalPredicatesNeg[n_goalPredicatesNeg].n_var = 0;
					i = 0;
				}
				else{
					aux[i] = a;
					i++;
				}
			}
			
			//read variables
			else{
				if(a == ')' || a == ','){
					//add it to the structure
					aux[i] = '\0';
					strcpy(goalPredicatesNeg[n_goalPredicatesNeg].variables[goalPredicatesNeg[n_goalPredicatesNeg].n_var], aux);
					goalPredicatesNeg[n_goalPredicatesNeg].n_var++;
					i = 0;
					
					//closed parenthesis
					if(a == ')'){
						n_goalPredicatesNeg++;
						openParenthesis = false;
					}
				}
				else{
					aux[i] = a;
					i++;
				}
			}
		}
		
		a = getchar();
	}
}
//GROUNDING FUNCTIONS---------------------------------------------------

//return the index of the variable in the hash
int findHash(string variable){
	int i;
	
	for(i = 0; i < n_hash; i++){
		if(strcmp(hash_key[i], variable) == 0)
			return i;
	}
	
	return -1;
}

//generate all the possible combinations in numbers
char* possibleCombinations(string current, int x, bool added[]){
	int i;
	string current2, aux1, aux2;
	char *result = (char *)malloc(1000 * sizeof(char));
	bool added2[n_constants];
	
	for(i = 0; i < n_constants; i++)
		added2[i] = added[i];
		
	if(x > 0){
		strcpy(aux2, current);
		
		for(i = 0; i < n_constants; i++){
			if(!added2[i]){
				added2[i] = true;
				sprintf(aux1, "%d ", i);
				strcpy(current2, aux2);
				strcat(current2, aux1);
				strcat(result, possibleCombinations(current2, x - 1, added2));
				added2[i] = false;
			}
		}
		
		return result;
	}
	else{
		strcpy(aux1, current);
		return strcat(aux1, "\n ");
	}
}

//translates the combinations to refer to the constants, put in a matrix of strings
char*** translateCombinations(string combinations, int *k){
	char *p, ***mat;
	int i, j;
	
	mat = (char ***)malloc(1000 * sizeof(char**));
	
	for(i = 0; i < 1000; i++){ 
		mat[i] = (char **)malloc(100 * sizeof(char*));
		
		for(j = 0; j < 100; j++)
			mat[i][j] = (char *)malloc(1000 * sizeof(char));
	}
		
	p = strtok(combinations, " ");
	i = 0;
	j = 0;
	while(p != NULL){
		if(p[0] == '\n'){
			i++;
			j = 0;
		}
		else{
			strcpy(mat[i][j], constants[atoi(p)]);
			j++;
		}
		
		p = strtok(NULL, " ");
	}
	
	*k = i;
	return mat;
}

//check if a string is a variable
bool isVariable(string s){
	if(s[0] > 96 && s[0] < 123)
		return true;
	else
		return false;
}

//ground an action
void groundAction(int index){
	bool added[n_constants];
	int i, total_comb, j, k, hash_index;
	char *comb_temp, ***comb;
	action act; 
	
	for(i = 0; i < n_constants; i++)
		added[i] = false;
	
	//copy some parameters
	act.n_var = actions[index].n_var;
	act.n_pre = actions[index].n_pre;
	act.n_preNeg = actions[index].n_preNeg;
	act.n_del = actions[index].n_del;
	act.n_add = actions[index].n_add;
	strcpy(act.label, actions[index].label);
	
	//count the number of arguments that are constants
	k = 0;
	for(i = 0; i < actions[index].n_var; i++){
		if(isVariable(actions[index].variables[i]))
			k++;
	}
	
	//generate all the possible combinations
	comb_temp = possibleCombinations("", k, added);
	comb = translateCombinations(comb_temp, &total_comb);
	
	//ground the actions	
	n_hash = act.n_var;
	
	for(i = 0; i < total_comb; i++){
		//ground variables
		for(j = 0; j < actions[index].n_var; j++){
			//creates hash
			strcpy(hash_key[j], actions[index].variables[j]);
			strcpy(hash_result[j], comb[i][j]);
			
			strcpy(act.variables[j], comb[i][j]);
		}
		
		//ground preconditions
		for(j = 0; j < actions[index].n_pre; j++){
			act.pre[j].n_var = actions[index].pre[j].n_var;
			strcpy(act.pre[j].label, actions[index].pre[j].label);
			
			for(k = 0; k < act.pre[j].n_var; k++){
				if(isVariable(actions[index].pre[j].variables[k])){
					hash_index = findHash(actions[index].pre[j].variables[k]);
					strcpy(act.pre[j].variables[k], hash_result[hash_index]);
				}
				else
					strcpy(act.pre[j].variables[k], actions[index].pre[j].variables[k]);
			}
		}
		
		//ground negative preconditions
		for(j = 0; j < actions[index].n_preNeg; j++){
			act.preNeg[j].n_var = actions[index].preNeg[j].n_var;
			strcpy(act.preNeg[j].label, actions[index].preNeg[j].label);
			
			for(k = 0; k < act.preNeg[j].n_var; k++){
				if(isVariable(actions[index].preNeg[j].variables[k])){
					hash_index = findHash(actions[index].preNeg[j].variables[k]);
					strcpy(act.preNeg[j].variables[k], hash_result[hash_index]);
				}
				else
					strcpy(act.preNeg[j].variables[k], actions[index].preNeg[j].variables[k]);
			}
		}
		
		//ground deletes
		for(j = 0; j < actions[index].n_del; j++){
			act.del[j].n_var = actions[index].del[j].n_var;
			strcpy(act.del[j].label, actions[index].del[j].label);
			
			for(k = 0; k < act.del[j].n_var; k++){
				if(isVariable(actions[index].del[j].variables[k])){
					hash_index = findHash(actions[index].del[j].variables[k]);
					strcpy(act.del[j].variables[k], hash_result[hash_index]);
				}
				else
					strcpy(act.del[j].variables[k], actions[index].del[j].variables[k]);
			}
		}
		
		//ground adds
		for(j = 0; j < actions[index].n_add; j++){
			act.add[j].n_var = actions[index].add[j].n_var;
			strcpy(act.add[j].label, actions[index].add[j].label);
			
			for(k = 0; k < act.add[j].n_var; k++){
				if(isVariable(actions[index].add[j].variables[k])){
					hash_index = findHash(actions[index].add[j].variables[k]);
					strcpy(act.add[j].variables[k], hash_result[hash_index]);
				}
				else
					strcpy(act.add[j].variables[k], actions[index].add[j].variables[k]);
			}
		}
		
		//add it to the grounded actions
		groundedActions[n_groundedActions] = act;
		n_groundedActions++;
	}
}

//QUEUE FUNCTIONS---------------------------------------------------

//insert in the end of the queue
void insertQueue(tree t, int g, float h){
	queue[n_queue].t = t;
	queue[n_queue].g = g;
	queue[n_queue].h = h;
	
	n_queue++;
}

//remove the first element from the queue
void removeQueue(tree *t, int *g, float *h){
	int i;
	
	*t = queue[0].t;
	*g = queue[0].g;
	*h = queue[0].h;
	//shift the elements
	for(i = 0; i < n_queue; i++){
		queue[i].t = queue[i+1].t;
		queue[i].g = queue[i+1].g;
		queue[i].h = queue[i+1].h;
	
	}
	
	n_queue--;
}

//order queue  according to f value
void orderQueue(){
	int i, j;
	queue_vector a;
	
	for(i = 0; i < n_queue; i++){
        for(j = i + 1; j < n_queue; j++){
            if(queue[i].g + queue[i].h > queue[j].g + queue[j].h){
                a.g = queue[i].g;
                a.h = queue[i].h;
                a.t = queue[i].t;
                queue[i].g = queue[j].g;
                queue[i].h = queue[j].h;
                queue[i].t = queue[j].t;
                queue[j].g = a.g;
                queue[j].h = a.h;
                queue[j].t = a.t;
            }
        }
    }
}

//PLANNING FUNCTIONS---------------------------------------------------

//compare two predicates
bool comparePredicates(predicate a, predicate b){
	int i;
	
	if(strcmp(a.label, b.label) != 0)
		return false;
	
	for(i = 0; i < a.n_var; i++){
		if(strcmp(a.variables[i], b.variables[i]) != 0)
			return false;
	}
	
	return true;
}

//check if a state meets the action requirements
bool checkPreconditions(tree s, action a){
	int i, j;
	bool flag;
	
	//checks preconditions
	for(i = 0; i < a.n_pre; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(s -> predicates[j], a.pre[i])){
				flag = true;
				break;
			}
		}
		
		if(!flag)
			return false;
	}
	
	//check negative preconditions
	for(i = 0; i < a.n_preNeg; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(s -> predicates[j], a.preNeg[i])){
				flag = true;
				break;
			}
		}
		
		if(flag)
			return false;
	}
	
	return true;
}

//constructs the resultant state after applying an action
tree applyAction(tree s, action a){
	int i, j;
	bool flag;
	tree result = malloc(sizeof(node));
	
	//predicates
	for(i = 0; i < s -> n_predicates; i++){
		//search for the predicate in the deletes
		flag = false;
		for(j = 0; j < a.n_del; j++){
			if(comparePredicates(s -> predicates[i], a.del[j]))
				flag = true;
		}
		
		//ignore this predicate
		if(!flag){
			//copy to the result state
			result -> predicates[result -> n_predicates] = s -> predicates[i];
			result -> n_predicates++;
		}
	}
	
	//add to the predicates the adds
	for(i = 0; i < a.n_add; i++){
		//check if it is already there
		flag = false;
		for(j = 0; j < result -> n_predicates; j++){
			if(comparePredicates(result -> predicates[j], a.add[i]))
				flag = true;
		}
		
		//if it is not there, add it
		if(!flag){
			result -> predicates[result -> n_predicates] = a.add[i];
			result -> n_predicates++;
		}
	}
	
	sprintf(result -> act, "%s", printAction(a));
	result -> n_childs = 0;
		
	return result;
}

//check if a state meets the goal requirements
bool isGoal(tree s){
	int i, j;
	bool flag;
	
	//check if meets goal predicates	
	for(i = 0; i < goal -> n_predicates; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(goal -> predicates[i], s -> predicates[j])){
				flag = true;
				break;
			}
		}
		
		if(!flag)
			return false;
	}
	
	//check if meets goal negative predicates	
	for(i = 0; i < n_goalPredicatesNeg; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(goalPredicatesNeg[i], s -> predicates[j])){
				flag = true;
				break;
			}
		}
		
		if(flag)
			return false;
	}
	
	return true;
}

//checks if it finds a duplicate state
int checkDuplicate(tree t, tree child){
	int i, j;
	bool flag;
	if(t != NULL){
		if(t -> n_predicates != child -> n_predicates)
			goto branch;
		
		for(i = 0; i < t -> n_predicates; i++){
			flag = false;
			
			for(j = 0; j < child -> n_predicates; j++){ 
				if(comparePredicates(t -> predicates[i], child -> predicates[j])){
					flag = true;
					break;
				}
			}
			
			if(!flag)
				goto branch;
		}
		
		return true;

branch:
		for(i = 0; i < t -> n_childs; i++){
			if(checkDuplicate(t -> childs[i], child))
				return true;
		}
	}
	
	return false;
}

//count the number of unachieved goals
int countUnachieved(tree s){
	int i, j, k = 0;
	bool flag;
	
	for(i = 0; i < goal -> n_predicates; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(goal -> predicates[i], s -> predicates[j])){
				flag = true;
				break;
			}
		}
		
		if(!flag)
			k++;
	}
	
	//check if meets goal negative predicates	
	for(i = 0; i < n_goalPredicatesNeg; i++){
		flag = false;
		
		for(j = 0; j < s -> n_predicates; j++){
			if(comparePredicates(goalPredicatesNeg[i], s -> predicates[j])){
				flag = true;
				break;
			}
		}
		
		if(flag)
			k++;
	}
	
	return k;
}

//implements A* algorithm(h = 0, so it is just like BFS)
tree astar(int x){
	tree t, child;
	int i, g = 0, possibleActions[100], n_possibleActions;
	float h = 0;
	
	insertQueue(initial, g, h);
	
	while(n_queue > 0){
		//remove the first element of the queue
		removeQueue(&t, &g, &h);
		
		//increments the number of nodes expanded
		expanded++;
		
		//find all the possible actions
		n_possibleActions = 0;
		for(i = 0; i < n_groundedActions; i++){
			if(checkPreconditions(t, groundedActions[i])){
				possibleActions[n_possibleActions] = i;
				n_possibleActions++;
			}
		}
		
		//for each action, add it into the queue
		for(i = 0; i < n_possibleActions; i++){
			child = applyAction(t, groundedActions[possibleActions[i]]);
			
			if(!checkDuplicate(initial, child)){
				//insert in the tree
				t -> childs[t -> n_childs] = child;
				t -> n_childs++;
				child -> parent = t;
				generated++;
				
				//founded goal
				if(isGoal(child))
					return child;
					
				//add to the queue
				else{
					if(x == 0)
						insertQueue(child, g + 1, 0);
					else
						insertQueue(child, g + 1, w * countUnachieved(child));
				}
			}
		}
		
		orderQueue();
	}
	
	return NULL;
}

//DEBUG FUNCTIONS---------------------------------------------------

//print a predicate
void printPredicate(predicate p){
	int i;
	
	printf("%s ", p.label);
	for(i = 0; i < p.n_var; i++)
		printf("%s ", p.variables[i]);
	printf("\n");
}

//print an action
char* printAction(action a){
	int i;
	char *result = malloc(100 * sizeof(char));
	
	sprintf(result, "%s ", a.label);
	for(i = 0; i < a.n_var; i++){
		strcat(result, a.variables[i]);
		strcat(result, " ");
	}
	strcat(result, "\n");
	
	return result;
}
