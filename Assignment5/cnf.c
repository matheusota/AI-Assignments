#include "functions.h"

//set variable x as true
void setVariable(int x){
	list l;
	
	//positive literal
	if(x > 0){
		variables[x].state = 1;
		
		//set as true the clauses where the literal appears
		for(l = (variables[x].posOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[x] = 0;
			(*(l -> clause)).pos--;
			
			if((*(l -> clause)).subsumedBy == 0){
				(*(l -> clause)).subsumedBy = x;
			}
		}
		
		//shortens clauses where negated literal appears
		for(l = (variables[x].negOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[x] = 0;
			(*(l -> clause)).neg--;
		}
	}
	
	//negated literal
	else{
		variables[-x].state = -1;
		
		//set as true the clauses where negated literal appears
		for(l = (variables[-x].negOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[-x] = 0;
			(*(l -> clause)).neg--;
				
			if((*(l -> clause)).subsumedBy == 0){
				(*(l -> clause)).subsumedBy = -x;
			}
		}
		
		//shortens clauses where the literal appears
		for(l = (variables[-x].posOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[-x] = 0;
			(*(l -> clause)).pos--;
		}
	}
	
}

//reverse set variable process
void reverseSetVariable(int x){
	list l;
	
	//positive literal
	if(x > 0){
		variables[x].state = 0;
		
		//unsolve clauses where the literal appears
		for(l = (variables[x].posOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[x] = 1;
			(*(l -> clause)).pos++;
			
			if((*(l -> clause)).subsumedBy == x){
				(*(l -> clause)).subsumedBy = 0;
			}
		}
		
		//replace negated literal
		for(l = (variables[x].negOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[x] = -1;
			(*(l -> clause)).neg++;
		}
	}
	
	//negated literal
	else{
		variables[-x].state = 0;
		
		//unsolve clauses where negated literal appears
		for(l = (variables[-x].negOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[-x] = -1;
			(*(l -> clause)).neg++;
			
			if((*(l -> clause)).subsumedBy == -x){
				(*(l -> clause)).subsumedBy = 0;
			}
		}
		
		//replace literal
		for(l = (variables[-x].posOccList) -> next; l != NULL; l = l -> next){
			(*(l -> clause)).literals[-x] = 1;
			(*(l -> clause)).pos++;
		}
	}
}

//Unit Propagation, returns true if unit propagation is possible, false otherwise
void unitPropagate(int *propagate_stack){
	int i, x = 0;
	list l;
	
	//find unit clause
	for(i = 1; i <= m; i++){
		if(clauses[i].pos + clauses[i].neg == 1 && clauses[i].subsumedBy == 0){
			for(x = 1; clauses[i].literals[x] == 0; x++);
			
			x = clauses[i].literals[x]*x;	
			break;
		}
	}
	
	//if there is an unit clause
	if(x != 0){
		(*propagate_stack)++;
		push(x);
		setVariable(x);
		unitPropagate(propagate_stack);
	}
}

//reverse the actions of n variables in the stack
void reverseVariables(int n){
	while(n > 0){
		reverseSetVariable(pop());
		n--;
	}
}

//implementation of the Davis-Logemann-Loveland Algorithm
bool DLL(){
	int i, propagate_stack;
	bool no_clauses, result;
	
	//Unit Propagate
	propagate_stack = 0;
	unitPropagate(&propagate_stack);
	
	for(i = 1; i <= m; i++){
		if(clauses[i].pos + clauses[i].neg == 0 && clauses[i].subsumedBy == 0){
			//reverse actions
			reverseVariables(propagate_stack);
			return false;
		}
	}
	
	//check if all clauses are solved
	no_clauses = true;
	
	for(i = 1; i <= m; i++){
		if(clauses[i].subsumedBy == 0)
			no_clauses = false;
	}
	
	if(no_clauses)
		return true;
	
	//set a variable
	for(i = 1; i <= n; i++){
		if(variables[i].state == 0){
			push(i);
			setVariable(i);
			break;
		}
	}
	
	//call dll recursively
	if(DLL())
		return true;
		
	else{
		reverseVariables(1);
		
		//increment number of nodes generated
		nodes++;
		
		//set the negated variable
		push(-i);
		setVariable(-i);

		//call dll recursively
		result = DLL();
		
		//backtrack if it didn't solved
		if(!result)
			reverseVariables(propagate_stack + 1);
		
		return result;
	}
}
