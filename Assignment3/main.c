#include "functions.h"

int main(int argc, char **argv){
	int i, j;
	double x, y;
	char a;
	
	//scan the size of the matrix
	scanf("%d %d", &m, &n);
	
	//scan the matrix itself
	getchar();
	for(i = 0; i < n; i++){
		
		for(j = 0; j < m; j++)
			w[i][j] = getchar();
		
		//throw away break line
		a = getchar();
	}
	
	scanf("%lf", &x);
	scanf("%lf", &y);
	
	scanf("%lf", &goal_x);
	scanf("%lf", &goal_y);
	
	printRRT(x, y);
	
	return 0;
}

