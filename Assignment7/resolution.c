#include "functions.h"

//return a tree resulted of applying resolution rule
tree resolution(tree t1, tree t2, tree model, int axiom_id){
	tree result = malloc(sizeof(tree_node));
	int i;
	bool temp = model -> childs[0] -> negative;
	
	n_resolutions++;
	
	//change to match if trees are equal
	model -> childs[0] -> negative = !model -> childs[0] -> negative;
	
	//head of the tree
	strcpy(result -> label, "@");
	result -> n_childs = 0;
	result -> axiom_id = axiom_id + 1;
	
	//copy to the result tree all the clauses that dont start with the label
	for(i = 0; i < t1 -> n_childs; i++){
		if(!compareTrees(t1 -> childs[i], model)){
			result -> childs[result -> n_childs] = copyTree(t1 -> childs[i], NULL);
			result -> childs[result -> n_childs] -> axiom_id = axiom_id + 1;
			result -> n_childs++;
		}
	}
	
	for(i = 0; i < t2 -> n_childs; i++){
		if(!compareTrees(t2 -> childs[i], model)){
			result -> childs[result -> n_childs] = copyTree(t2 -> childs[i], NULL);
			result -> childs[result -> n_childs] -> axiom_id = axiom_id + 1;
			result -> n_childs++;
		}
	}
	
	model -> childs[0] -> negative = temp;
	
	return result;
}

//for each clause in the query, find the candidates and attempt to unify
bool queryUnify(){
	int i, j, k, m, index, axiom_id, t, n_candidates;
	tree temp, current, candidates[1000];
	
	//for each clause of the queries
	for(m = 0; m < n_query; m++){
start_loop:
		
		current = query[m];
		getNextOut();
		
		//remove from the query array and insert to the KB
		removeQueryInsertAxiom(m);
		
		//for each predicate inside the clause
		for(i = 0; i < current -> n_childs; i++){
			
			//list the nodes on the query clause
			n_nodes_listed = 0;
			listNodes(current -> childs[i]);
			n_candidates = 0;
			
			//first we find the candidates
			
			//for each node label, find where it appears in the axioms
			for(j = 0; j < n_nodes_listed; j++){
				index = findTermList(nodesListed[j]);
				
				if(index != -1){
					//for each clause where the term appears
					for(k = 0; k < termlist[index].n_pointers; k++){
						
						//if they have different polarity, add as a candidate
						if(current -> childs[i] -> childs[0] -> negative != (termlist[index].pointers[k]) -> childs[0] -> negative){
							candidates[n_candidates] = termlist[index].pointers[k];
							n_candidates++;
						}
					}
				}
			}

			//for each candidate, tries to unify
			for(j = 0; j < n_candidates; j++){
				
				if(unifier(current -> childs[i] -> childs[0], candidates[j] -> childs[0])){
					axiom_id = candidates[j] -> childs[0] -> axiom_id;
					temp = resolution(current, axioms[axiom_id], current -> childs[i], treeOut -> axiom_id);
					
					//check if the result wasnt already in the KB
					if(!alreadyAnAxiom(temp)){
						//empty clause
						if(temp -> n_childs == 0){		
							//insert into the output tree
							treeOut = insertOutputNode(temp, treeOut, current -> childs[i] -> axiom_id, candidates[j] -> axiom_id, temp -> axiom_id, true);
							return true;
						}
						//add resulted clause to the query	
						else{
							query[n_query] = temp;
							cleanVar();
							n_query++;
							
							//insert into the output tree
							printf("%d\n", n_out);
							nextOut[n_out] = insertOutputNode(temp, treeOut, current -> childs[i] -> axiom_id, candidates[j] -> axiom_id, temp -> axiom_id, false);
							n_out++;
						}
					}
				}
			}
			
			if(n_query == 1){
				m = 0;
				goto start_loop;
			}
		}
	}
	
	return false;
}
