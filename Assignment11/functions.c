#include "functions.h"

//if is a commentary line, ignore it
void ignoreComments(){
	char a = getchar();
	
	while(a != '\n')
		a = getchar();
}

//return index of a random data point
int getRandomPoint(){
	return rand() % n_data;
}

//get distance to line
float getDistancePoint2Line(int x, int y, float slope, float intercept){
	return abs(slope * x - y + intercept) / sqrt(slope * slope + 1);
}

//find inliers of a line
void findInliers(float slope, float intercept, point* inliers, int *n_inliers){
	int i;
	*n_inliers = 0;
	
	for(i = 0; i < n_data; i++){
		if(getDistancePoint2Line(data[i].x, data[i].y, slope, intercept) <= 2){
			inliers[*n_inliers].x = data[i].x;
			inliers[*n_inliers].y = data[i].y;
			(*n_inliers)++;
		}
	}
}

//project a point into a line
point projection(float slope, float intercept, point p){
	float slope2 = -(1.0 / slope);
	float intercept2 = p.y - p.x * slope2;
	point result;
	
	if(p.y != slope * p.x + intercept){
		result.x = (intercept2 - intercept) / (slope - slope2);
		result.y = slope2 * result.x + intercept2;
		return result;
	}
	else
		return p;
}

//get the biggest segment of an inliers set
segment getBiggestSegment(float slope, float intercept, point* inliers, int* n_inliers){
	int i, j, n_array = 0, big, index_big, index_start[1000], index_end[1000];
	float u[1000], aux;
	segment segArray[1000];
	point p;
	
	//get u values
	for(i = 0; i < *n_inliers; i++)
		u[i] = (inliers[i].x + (inliers[i].y - intercept) * slope) / sqrt(slope * slope + 1);
		
	//sort u values
	for(i = 0; i < *n_inliers; i++){
        for(j = i + 1; j < *n_inliers; j++){
            if(u[i] > u[j]){
                aux = u[i];
                p = inliers[i];
                
                u[i] = u[j];
                inliers[i] = inliers[j];
                
                u[j] = aux;
                inliers[j] = p;
            }
        }
    }
	
	//prepare segments
	segArray[0].start = projection(slope, intercept, inliers[0]);
	segArray[0].n_inliers = 1;
	index_start[0] = 0;
	for(i = 1; i <= *n_inliers; i++){
		if(i == *n_inliers || u[i] - u[i-1] > 4){
			index_end[n_array] = i - 1;
			index_start[n_array + 1] = i;
			
			segArray[n_array].end = projection(slope, intercept, inliers[i-1]);
			segArray[n_array + 1].start = projection(slope, intercept, inliers[i]);
			segArray[n_array + 1].n_inliers = 1;
			
			n_array++;
		}
		else
			segArray[n_array].n_inliers++;
	}
	
	//get biggest segment
	big = -1;
	index_big = 0;
	for(i = 0; i < n_array; i++){
		if(segArray[i].n_inliers > big){
			index_big = i;
			big = segArray[i].n_inliers;
		}
    }
    
    //update inliers
    *n_inliers = 0;
    for(i = index_start[index_big]; i <= index_end[index_big]; i++){
		inliers[*n_inliers] = inliers[i];
		(*n_inliers)++;
	}
    
    return segArray[index_big];
}

//apply linear regression to a set of points
segment linearRegression(point* inliers, int* n_inliers){
	float sumY = 0, sumX = 0;
	int i;
	
	//apply regression
	for(i = 0; i < *n_inliers; i++){
		sumX += inliers[i].x;
		sumY += inliers[i].y;
	}

	float xbar = sumX / *n_inliers;
	float ybar = sumY / *n_inliers;

	float xxbar = 0.0;
	float xybar = 0.0;

	for(i = 0; i < *n_inliers; i++){
		xxbar += (inliers[i].x - xbar) * (inliers[i].x - xbar);
		xybar += (inliers[i].x - xbar) * (inliers[i].y - ybar);
	}

	float slope = xybar / xxbar;
	float intercept = ybar - slope * xbar;
	
	//return the biggest segment
	return getBiggestSegment(slope, intercept, inliers, n_inliers);
}

//copy one array of points to the other
void copyPoints(point* dest, point* source, int n_source){
	int i;
	
	for(i = 0; i < n_source; i++)
		dest[i] = source[i];
}

//remove an element from the data set
void removeFromData(int index){
	int i;
	
	for(i = index; i < n_data; i++)
		data[i] = data[i + 1];
	
	n_data--;
}

//remove the inliers of a segment
void removeInliers(segment s){
	float slope = (s.end.y - s.start.y) / (s.end.x - s.start.x);
	float intercept = s.start.y - slope * s.start.x;
	int i;
		
	for(i = 0; i < n_data; i++){
		if(data[i].x >= s.start.x && data[i].x <= s.end.x && getDistancePoint2Line(data[i].x, data[i].y, slope, intercept) <= 2){
			removeFromData(i);
			i--;
		}
	}
}
	
