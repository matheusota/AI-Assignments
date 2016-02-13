#include "functions.h"

//set variable x as true
void setVariable(int x){
	
	//positive literal
	if(x > 0){
		variable[x-1].state = 1;
		
		//set as true the clauses where the literal appears
		for(l = variables[x-1].posOccList -> next; l != NULL; l = l -> next){
			if(*(l -> clause).subsumedBy == -1)
				*(l -> clause).subsumedBy == x-1;
		}
		
		//shortens clauses where negated literal appears
		for(l = variables[x-1].negOccList -> next; l != NULL; l = l -> next){
			*(l -> clause).neg--;
		}
	}
	
	//negated literal
	else{
		variable[-x-1].state = 0;
		
		//set as true the clauses where negated literal appears
		for(l = variables[-x-1].negOccList -> next; l != NULL; l = l -> next){
			if(*(l -> clause).subsumedBy == -1)
				*(l -> clause).subsumedBy == -x-1;
		}
		
		//shortens clauses where the literal appears
		for(l = variables[-x-1].posOccList -> next; l != NULL; l = l -> next){
			*(l -> clause).pos--;
		}
	}
}

//reverse set variable process
void reverseSetVariable(int x){
	
	//positive literal
	if(x > 0){
		variable[x-1].state = -1;
		
		//unsolve clauses where the literal appears
		for(l = variables[x-1].posOccList -> next; l != NULL; l = l -> next){
			if(*(l -> clause).subsumedBy == x-1)
				*(l -> clause).subsumedBy == -1;
		}
		
		//replace negated literal
		for(l = variables[x-1].negOccList -> next; l != NULL; l = l -> next)
			*(l -> clause).neg++;
	}
	
	//negated literal
	else{
		variable[-x-1].state = -1;
		
		//unsolve clauses where negated literal appears
		for(l = variables[-x-1].negOccList -> next; l != NULL; l = l -> next){
			if(*(l -> clause).subsumedBy == -x-1)
				*(l -> clause).subsumedBy == -1;
		}
		
		//replace literal
		for(l = variables[-x-1].posOccList -> next; l != NULL; l = l -> next)
			*(l -> clause).pos++;
	}
}

//Unit Propagation, returns true if unit propagation is possible, false otherwise
void unitPropagate(){
	int i, x = 0;
	list l;
	
	//find unit clause
	for(i = 0; i < m; i++){
		if(clauses[i].pos + clauses[i].neg == 1){
			x = clauses[i].literals[0];
			break;
		}
	}
	
	//if there is an unit clause
	if(x != 0){
		push(x);
		setVariable(x);
		unitPropagate();
	}
}

//implementation of the Davis-Logemann-Loveland Algorithm
bool DLL(){
	int i;
	bool no_clauses;
	
	//increment number of nodes generated
	nodes++;
	
	//Unit Propagate
	unitPropagate();
	
	//check if there is an unsolved empty clause
	for(i = 0; i < m; i++){
		if(clauses[i].pos + clauses[i].neg == 0 && clauses[i].subsumedBy == -1){
			//reverse actions
			reverseSetVariable(pop());
			
			return false;
		}
	}
	
	//check if all clauses are solved
	no_clauses = false;
	
	for(i = 0; i < m; i++){
		if(clauses[i].subsumedBy == -1)
			no_clauses = true;
	}
	
	if(no_clauses)
		return true;
	
	//set a variable
	for(i = 0; i < n; i++){
		if(variables[i].state == -1){
			push(i+1);
			setVariable(i+1);
			break;
		}
	}
	
	//call dll recursively
	if(DLL())
		return true;
	
	else{
		//reverse actions
		reverseSetVariable(pop());
		
		//set the negated variable
		addStack(-i-1);
		setVariable(-i-1);
		
		//call dll recursively
		return DLL();
	}
}
