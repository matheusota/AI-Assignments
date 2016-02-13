#include "functions.h"

//READING FUNCTIONS---------------------------------------------------

//if is a commentary line, ignore it
void ignoreComments(){
	char a = getchar();
	
	while(a != '\n')
		a = getchar();
}

//read a state
void readState(int index){
	int i, aux;
	char a;
	
	states[index].id = index;
	//read the state parameters
	scanf("%f %d %d", &states[index].reward, &aux, &states[index].n_actions);
	
	if(aux == 1)
		states[index].n_actions = 0;
		
	i = 0;
	while(i < states[index].n_actions){
		a = getchar();
		
		if(a == '#')
			ignoreComments();
			
		else if(a == 45 || (a > 47 && a < 58)){
			ungetc(a, stdin);
			readAction(index, i);
			i++;
		}
	}
}

//read an action
void readAction(int state_index, int action_index){
	int i, id, n_states_aux;
	char a;
	string constant;
	action *act;
	
	act = malloc(sizeof(action));
	states[state_index].actions[action_index] = act;
	
	scanf("%d", &(act -> n_states));
	
	for(i = 0; i < act -> n_states; i++){
		scanf("%d", &id);
		act -> states[i] = &states[id];
		scanf("%f", &act -> probability[i]);
	}
}

//apply bellman equations for all states
void applyBellman(){
	int i, j, k, choosedAction;
	float sumStates, maxAction;
	
	for(i = 0; i < n_states; i++){
		maxAction = -9999;
		
		//terminal state
		if(states[i].n_actions == 0){
			choosedAction = -1;
			maxAction = 0;
		}
			
		else{
			for(j = 0; j < states[i].n_actions; j++){
				sumStates = 0;
				//sum the reward of the states linked to an action
				for(k = 0; k < states[i].actions[j] -> n_states; k++)
					sumStates = sumStates + states[i].actions[j] -> probability[k] * utility[0][states[i].actions[j] -> states[k] -> id];
					
				if(sumStates > maxAction){
					choosedAction = j;
					maxAction = sumStates;
				}
			}
		}
		
		//update the utility
		utility[1][i] = states[i].reward + discount * maxAction;
		utilityAction[i] = choosedAction;
	}
}

//find the max difference between utilities
float findDifference(){
	int i;
	float diff = 0;
	
	for(i = 0; i < n_states; i++){
		if(diff < fabs(utility[0][i] - utility[1][i]))
			diff = fabs(utility[0][i] - utility[1][i]);
	}
	
	return diff;
}

//print the domain
void printDomain(){
	int i, j, k;
	
	for(i = 0; i < n_states; i++){
		printf("STATE %d -> Reward: %f; Number of Actions: %d\n", i, states[i].reward, states[i].n_actions);
		
		for(j = 0; j < states[i].n_actions; j++){
			printf("\t ACTION %d\n", j);
			
			for(k = 0; k < states[i].actions[j] -> n_states; k++)
				printf("\t \t Go to STATE %d with Probability %f\n", states[i].actions[j] -> states[k] -> id, states[i].actions[j] -> probability[k]);
		}
	}
}
