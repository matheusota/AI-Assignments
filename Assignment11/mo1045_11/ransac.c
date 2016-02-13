#include "functions.h"

//implementation of the ransac algorithm
void ransac(){
	int i, j, k = 0, index_p1, index_p2, n_inliers = 0, n_inliers2;
	float slope, intercept;
	point inliers[1000], inliers2[1000];
	segment segTemp1, segTemp2;
	
	while(n_data >= 8){
		segments[n_segments].n_inliers = 0;
		
		//try to find a segment to different models
		for(i = 0; i < 500; i++){
			//get 2 random points of the data set
			index_p1 = getRandomPoint();
			index_p2 = getRandomPoint();
			while(index_p1 == index_p2 || data[index_p2].x == data[index_p1].x)
				index_p2 = getRandomPoint();
			
			//fit the model
			slope = (data[index_p2].y - data[index_p1].y) / (data[index_p2].x - data[index_p1].x);
			intercept = data[index_p1].y - (slope * data[index_p1].x); 
			
			//find the inliers
			findInliers(slope, intercept, inliers, &n_inliers);
			
			//find the biggest segment
			segTemp1 = getBiggestSegment(slope, intercept, inliers, &n_inliers);
			
			//there is no point in continue trying if the segment explains all data
			if(segTemp1.n_inliers == n_data){
				segments[n_segments] = segTemp1;
				break;
			}
				
			//apply regression to the segment until it gets less inliers
			segTemp2.n_inliers = 0;
			while(1){
				copyPoints(inliers2, inliers, n_inliers);
				n_inliers2 = n_inliers;
				
				segTemp2 = linearRegression(inliers2, &n_inliers2);
				
				if(segTemp2.n_inliers > segTemp1.n_inliers){
					segTemp1 = segTemp2;
					copyPoints(inliers, inliers2, n_inliers2);
					n_inliers = n_inliers2;
				}
				
				else
					break;
			}
			
			//compare with the biggest segments until now
			if(segTemp1.n_inliers > segments[n_segments].n_inliers)
				segments[n_segments] = segTemp1;
		}
		
		if(segments[n_segments].n_inliers >= 8){
			//remove inliers of the segment
			removeInliers(segments[n_segments]);
			n_segments++;
		}
		else
			break;
	}
}
