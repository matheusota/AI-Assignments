#include "functions.h"

int main(){
	char line[1000];
	char *token, *line_id;
	int a, b, j, k, r, i = 0;
	
	n_vars = 0;
	n_lines = 0;
	
	//separate into predicates
	while(fgets(line, 1000, stdin) != NULL){
		removeSpaces(line);
		token = strtok_r(line,"|\n", &line_id);
		
		//loop for analyzing each predicate in the line
		j = 0;
		while(token != NULL){
			negative[i][j] = false;
			
			//negative polarity
			if(token[0] == '-'){
				token = &token[1];
				negative[i][j] = true;
			}
			
			//insert predicate into the tree
			predicates[i][j] = malloc(sizeof(tree_node));
			predicates[i][j] -> n_childs = 0;
			analyzePredicate(predicates[i][j], token, i);
			
			//go for next predicate
			token = strtok_r(NULL, "|\n", &line_id);
			j++;
		}
		
		preds_lines[i] = j;
		i++;
		n_lines++;
	}
	
	//try to unify clauses
	for(r = 0; r < n_lines; r++){
		for(k = r + 1; k < n_lines; k++){
			for(i = 0; i < preds_lines[r]; i++){
				for(j = 0; j < preds_lines[k]; j++)
					unifier(predicates[r][i] -> childs[0], predicates[k][j] -> childs[0]);
			}
		}
	}
	
	for(i = 0; i < n_lines; i++)
		printOutput(i);
	
	return 0;
}

