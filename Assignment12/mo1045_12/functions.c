#include "functions.h"

//check if a string is a number
bool isNumber(char *str){
    int i, length = strlen(str);
    
    for (i = 0; i < length; i++){
        if (!isdigit(str[i]) && str[i] != '.')
			return false;
	}
    
    return true;
}

//if is a commentary line, ignore it
void ignoreComments(){
	char a = getchar();
	
	while(a != '\n')
		a = getchar();
}

//check if a cell is blocked
bool isBlocked(point a){
	int i;
	
	//check border
	if(a.x == m || a.x < 0 || a.y == n || a.y < 0)
		return true;
	
	//check blocked cells
	for(i = 0; i < n_blocked; i++){
		if(a.x == blocked[i].x && a.y == blocked[i].y)
			return true;
	}
	
	return false;
}
	
//apply action
point applyAction(point current, int action){
	point result = current;
	char a;
	
	//set the randomness of the action
	int x = rand() % 10;
	
	//take action to the left
	if(x == 0){
		if(action == 0)
			action = 3;
		else
			action--;
		
		a = directions[action];
	}
	
	//take action to the right
	if(x == 1){
		if(action == 3)
			action = 0;
		else
			action++;
		
		a = directions[action];
	}
	
	//no move
	if(x == 2)
		a = 'x';
	
	//normal action
	else
		a = directions[action];
	
	//set resultant cell
	if(a == 'u')
		result.y--;
	
	else if(a == 'd')
		result.y++;
	
	else if(a == 'r')
		result.x++;
	
	else if(a == 'l')
		result.x--;
	
	if(!isBlocked(result))
		return result;
	else
		return current;
}

//return index of a random data point
point getRandomPoint(){
	point p;
	
	p.x = rand() % m;
	p.y = rand() % n;
	
	return p;
}

//convert the command
char convertCmd(char *command){
	if(strcmp(command, "NORTH") == 0)
		return 'u';
	if(strcmp(command, "SOUTH") == 0)
		return 'd';
	if(strcmp(command, "EAST") == 0)
		return 'r';
	if(strcmp(command, "WEST") == 0)
		return 'l';
}
	
//generate an initial set of particles
void startParticles(){
	int i;
	point p;
	
	for(i = 0; i < n_particles; i++){
		p = getRandomPoint();
		if(!isBlocked(p)){
			particles[i] = p;
			particles[i].prob = (float)1.0 / n_particles;
		}
		else
			i--;
	}
}

//apply a command to all particles
void moveParticles(char cmd){
	int i;
	point p;
	
	for(i = 0; i < n_particles; i++)
		particles[i] = applyAction(particles[i], cmd);
}

//weights each particle
void weightParticles(){
	int i;
	point p;
	float sum = 0;
	
	for(i = 0; i < n_particles; i++)
		particles[i].prob *= measureParticle(particles[i]);
	
	//normalize
	for(i = 0; i < n_particles; i++)
		sum += particles[i].prob;
	
	for(i = 0; i < n_particles; i++)
		particles[i].prob /= sum;
}


//measure a particle
float measureParticle(point p){
	float x = (p.x - mx)*(p.x - mx);
	float y = (p.y - my)*(p.y - my);
	return exp(-((x/(2.0f*sigma*sigma))+(y/(2.0f*sigma*sigma))));
}

//resample particles according to the weights
void resampleParticles()
{
	float w[n_particles], a;
	int i, j, indexes[n_particles], b, n2 = (int)0.1 * n_particles;
	double r;
	point old[n_particles], p;

	//set some variables
	for(i = 0; i < n_particles; i++){
		w[i] = particles[i].prob;
		indexes[i] = i;
		old[i] = particles[i];
	}

	//sort the probabilities into descending order
	for(i = 0; i < n_particles; i++){
        for(j = i + 1; j < n_particles; j++){
            if(w[i] > w[j]){
                a = w[i];
                w[i] = w[j];
                w[j] = a;
                
                b = indexes[i];
                indexes[i] = indexes[j];
                indexes[j] = b;
            }
        }
    }

	//compute cumulative probabilities
	for(i = 1 ; i < n_particles; i++)
		w[i] += w[i - 1];

	//compute the sample
	for (i = 0; i < n_particles - n2; i++) {
		r = (double)rand() / (double)RAND_MAX;

		for (j = 0; j < n_particles - 1; j++) {
			if (r <= w[j])
				break;
		}
		
		particles[i] = old[indexes[j]];
	}
	
	//rejuvenation
	for(; i < n2; i++){
		p = getRandomPoint();
		if(!isBlocked(p)){
			particles[i] = p;
			particles[i].prob = (float)1.0 / n2;
		}
		else
			i--;
	}
}

//prints the particles
void printParticles(){
	int i;
	
	for(i = 0; i < n_particles; i++)
		printf("%d %d %f\n", particles[i].x, particles[i].y, particles[i].prob);
}


