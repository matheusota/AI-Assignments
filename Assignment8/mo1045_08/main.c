#include "functions.h"

int main(int argc, char **argv){
	int i;
	char a;
	
	n_constants = 0;

	//scan initial domain descriptions
	while(true){		
		a = getchar();
		
		//commentary
		if(a == '#')
			ignoreComments();
			
		//predicates
		else if(a == 'p')
			readPredicates();
		
		//constants
		else if(a == 'c'){
			readConstants();
			break;
		}
	}
	
	scanf("%d", &n_moves);
	ignoreComments();
	
	//scan the actions
	i = 0;
	n_actions = 0;
	while(i < n_moves){
		a = getchar();
		
		if(a == '#')
			ignoreComments();
			
		else if(a != '\n'){
			ungetc(a, stdin);
			scanAction();
			i++;
		}
	}
	
	//scan additional constants
	while(true){
		a = getchar();
		
		if(a == '#')
			ignoreComments();
			
		else if(a == 'c'){
			readConstants();
			break;
		}
	}
	
	//ground actions
	n_groundedActions = 0;
	for(i = 0; i < n_actions; i++)
		groundAction(i);
	
	//scan initial and goal states
	while(true){
		a = getchar();
		
		//commentary
		if(a == '#')
			ignoreComments();
			
		//initial
		else if(a == 'i')
			scanInitial();
		
		//goal
		else if(a == 'g'){
			scanGoal();
			break;
		}
	}
	
	//call A*
	expanded = 0;
	generated = 1; //initial state is already generated
	w = atof(argv[1]);
	
	tree t = NULL;
	
	if(strcmp(argv[2], "h0") == 0)
		t = astar(0);
	else if(strcmp(argv[2], "h-goal-lits") == 0)
		t = astar(1);
	else
		printf("unknown heuristic\n");
	
	//print output	
	if(t != NULL){
		for(i = 0; t != NULL; i++){
			strcpy(output[i], t -> act);
			t = t -> parent;
		}
		n_output = i - 1;
		
		for(i = n_output - 1; i >= 0; i--)
			printf("%d %s", n_output - i - 1, output[i]);
	}
	else
		printf("No plan found.\n");
		
	printf("%d nodes generated\n", generated);
	printf("%d nodes expanded\n", expanded);	
	return 0;
}
