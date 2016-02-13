#include "functions.h"

int main(int argc, char **argv){
	int i, j;
	char a, cmd, str[100], userInput[10000], command[10];
    //FILE *tty = fopen("/dev/tty", "r"); redirect to terminal
	
	//ignore comments
	a = getchar();
	while(a == '/'){
		ignoreComments();
		a = getchar();
	}
	ungetc(a, stdin);
	
	//scan the size of the matrix
	scanf("%d %d", &m, &n);
	
	//scan the grid
	getchar();
	n_blocked = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			a = getchar();
			
			if(a == '#'){
				blocked[n_blocked].x = j;
				blocked[n_blocked].y = n - i - 1;
				n_blocked++;
			}
		}
		
		//throw away break line
		getchar();
	}
	
	//set random seed
	srand(time(NULL));
	
	strcpy(directions, "urdl");
	
	//set sigma and limit_particles
	if(argv[1] != NULL && strcmp(argv[1], "--sigma") == 0){
		sigma = atoi(argv[2]);
		
		//copy second argument
		if(argv[3] != NULL && strcmp(argv[3], "--particles") == 0){
			argv[1] = argv[3];
			argv[2] = argv[4];
		}
	}
	else
		sigma = 2;
	
	if(argv[1] != NULL && strcmp(argv[1], "--particles") == 0)
		n_particles = atoi(argv[2]);
	else
		n_particles = 100;
	
	//generate particles
	startParticles();

	//enter on perpetual loop
	while(true){
		fflush(stdin);
		scanf("%s", &str);
		
		if(strcmp(str, "END") == 0)
			break;
		else{
			mx = atof(str);
			
			scanf("%f", &my);
			
			scanf("%s", &command);
			
			cmd = convertCmd(command);
			
			//moves each particle
			moveParticles(cmd);
			
			//weights each particle
			weightParticles();
			
			//resample
			resampleParticles();
			
			//output particles
			printParticles();
		}
	}
	
	//fclose(tty);
		
	return 0;
}
