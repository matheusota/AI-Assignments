#include "functions.h"

int main(int argc, char **argv){
	int i, j;
	float difference;
	char a;

	//scan initial description
	while(true){		
		a = getchar();
		
		//commentary
		if(a == '#')
			ignoreComments();
			
		//number of states
		else if(a == 'n'){
			for(i = 0; i < 16; i++)
				getchar();
				
			scanf("%d", &n_states);
		}
		
		//start state
		else if(a == 's'){
			for(i = 0; i < 11; i++)
				getchar();
				
			scanf("%d", &start_state);
			break;
		}
	}
	
	discount = atof(argv[2]);
	bound = atof(argv[3]);
	
	//scan the states
	i = 0;
	while(i < n_states){
		a = getchar();
		
		//commentary
		if(a == '#')
			ignoreComments();
		
		else if(a == 45 || (a > 47 && a < 58)){
			ungetc(a, stdin);
			readState(i);
			i++;
		}
	}
	
	//printDomain();
	
	//initialize the utility function
	for(i = 0; i < n_states; i++)
		utility[1][i] = 0;
		
	//value iteration of bellman equations
	difference = 9999;
	while(difference > bound){
		//copy utility
		for(j = 0; j < n_states; j++)
			utility[0][j] = utility[1][j];
				
		applyBellman();
		backups = backups + n_states;
		
		difference = findDifference();
	}
	
	//print output
	for(i = 0; i < n_states; i++){
		if(utilityAction[i] != -1)
			printf("%d\n", utilityAction[i]);
		else
			printf("\n");
	}
	
	printf("%d backups performed.\n", backups);
		
	
		
	return 0;
}
