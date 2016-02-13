#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//string type
typedef char string[100];
struct state_aux;
struct action_aux;
 
//state struct
typedef struct state_aux{
	int id;
	float reward;
	int n_actions;
	struct action_aux* actions[50];
}state;

//action struct
typedef struct action_aux{
	int id;
	int n_states;
	float probability[50];
	state* states[50];
}action;

//global variables
int n_states; //total number of states
int start_state; //starting state
float discount; //discount factor
float bound; //threshold for the difference of values between iterations

state states[100000];
float utility[2][100000];//holds the ultility value of the states
int utilityAction[100000];//holds the ultility value of the states
int backups; //the number of backups

//reading functions
void ignoreComments();
void readState(int index);
void readAction(int state_index, int action_index);

//debug functions
void printDomain();

//value iteration of bellman equations
void applyBellman();
float findDifference();


