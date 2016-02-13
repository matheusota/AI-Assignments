#include "functions.h"

int main(int argc, char **argv){
	int i, j;
	float x, y;
	char a;
	
	n_data = 0;
	
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
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			a = getchar();
			
			if(a == '#'){
				data[n_data].x = j;
				data[n_data].y = n - i - 1;
				n_data++;
			}
		}
		
		//throw away break line
		getchar();
	}
	
	//set random seed
	srand(time(NULL));
	
	//run ransac algorithm
	ransac();
	
	//print output
	printf("number of circles: 0\n");
	printf("number of lines: %d\n", n_segments);
	for(i = 0; i < n_segments; i++)
		printf("%f %f %f %f\n", segments[i].start.x, segments[i].start.y, segments[i].end.x, segments[i].end.y);
		 
	return 0;
}
