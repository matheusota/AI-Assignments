#include "functions.h"

//find, if possible, the most general unifier
bool unifier(tree t1, tree t2){
	bool result, var1, var2;
	tree aux;
	int i;
	 
	//see if there is already a tree associated with the variable
	i = findVar(t1 -> label);
	if(i != -1 && variables[i].t != NULL)
		t1 = variables[i].t;
	
	i = findVar(t2 -> label);
	if(i != -1 && variables[i].t != NULL)
		t2 = variables[i].t;
		
	//set boolean variables	
	result = true;
	var1 = isVariable(t1 -> label);
	var2 = isVariable(t2 -> label);
	
	//comparing step
	if(strcmp(t1 -> label, t2 -> label) == 0)
		goto advance;
	 
	//substitution step
	else{
		//neither of the two labels are variables
		if(!var1 && !var2)
			return false;
		
		//if the node on t1 is a variable
		else if(var1 && !var2){
			//founded variable with the same name on t2
			if(findLabel(t2, t1 -> label))
				return false;
			//associate t2 with the variable
			else{
				treeToVar(t2, t1 -> label);
				t1 = t2;
			}
		}
		
		//if the node on t2 is a variable
		else{
			//founded variable with the same name on t1
			if(findLabel(t1, t2 -> label))
				return false;
			//associate t1 with the variable
			else{
				treeToVar(t1, t2 -> label);
				t2 = t1;
			}
		}
	}
	
	advance:
	if(t1 -> n_childs == 0 && t2 -> n_childs == 0)
		return true;
	else{
		//call for the next childs on both trees
		for(i = 0; result && (i < t1 -> n_childs) && (i < t1 -> n_childs); i++)
			result = result && unifier(t1 -> childs[i], t2 -> childs[i]);
		
		return result; 
	}
}
