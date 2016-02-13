#include "functions.h"

int main(){
	char line[1000];
	char *token, *line_id;
	int a, b, j, k, r, i = 0;
	tree query_aux[1000];
	
	//initialize global variables
	n_vars = 0;
	n_terms = 0;
	n_query = 0;
	n_out = 0;
	n_resolutions = 0;
	
	//separate into predicates
	while(fgets(line, 1000, stdin) != NULL){
		//stop on --- negated query --- line
		if(strcmp(line, "--- negated query ---\n") == 0)
			break;
			
		removeSpaces(line);
		token = strtok_r(line,"|\n", &line_id);
		
		//insert new axiom into the KB
		axioms[i] = malloc(sizeof(tree_node));
		strcpy(axioms[i] -> label, "@");
		
		//loop for analyzing each predicate in the line
		j = 0;
		while(token != NULL){
			axioms[i] -> n_childs = j + 1;
			axioms[i] -> childs[j] = malloc(sizeof(tree_node));
			axioms[i] -> childs[j] -> axiom_id = i;
			strcpy(axioms[i] -> childs[j] -> label, "@");
			
			analyzePredicate(axioms[i] -> childs[j], axioms[i] -> childs[j], token, i);
			
			//go for next predicate
			token = strtok_r(NULL, "|\n", &line_id);
			j++;
		}
		
		i++;
	}
	
	n_axioms = i;
	
	//add negated query
	while(fgets(line, 1000, stdin) != NULL){
		removeSpaces(line);
		token = strtok_r(line,"|\n", &line_id);
		
		//insert query into the tree
		query[0] = malloc(sizeof(tree_node));
		strcpy(query[0] -> label, "@");
		query[0] -> n_childs = i;
		query[0] -> axiom_id = n_axioms;
		
		//loop for analyzing each predicate in the query
		i = 0;
		while(token != NULL){
			query[0] -> n_childs = i + 1;
			query[0] -> childs[i] = malloc(sizeof(tree_node));
			query[0] -> childs[i] -> axiom_id = n_axioms;

			strcpy(query[0] -> childs[i] -> label, "@");
			
			analyzePredicate(query[0] -> childs[i], query[0] -> childs[i], token, -1);
			
			//go for next predicate
			token = strtok_r(NULL, "|\n", &line_id);
			i++;
		}
	}
	n_query++;
	
	for(i = 0; i < n_axioms; i++)
		printOutput(i);
		
	//creates a starting output node with the query
	nextOut[0] = insertOutputNode(query[0], NULL, -1, -1, i + 1, false);
	n_out++;
	
	if(queryUnify()){
		traverseOutput();
		
		for(i = n_out - 1; i >= 0; i--)
			printOutputResolution(nextOut[i] -> t, nextOut[i] -> parent, nextOut[i] -> axiom_id1, nextOut[i] -> axiom_id2, nextOut[i] -> axiom_id, nextOut[i] -> done);
	}
	else
		printf("No proof exists.\n", n_resolutions);
		
	printf("%d total resolutions.\n", n_resolutions);
	
	return 0;
}

