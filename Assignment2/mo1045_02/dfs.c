#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*executes depth first search on the world to find the plan to clean it
it returns 1 if founded a way to collect all dirt, else it returns 0*/
int dfs(int x, int y, int dirt, int level, int limit){
	int instruction = 0; //0 -> U, 1 -> D, 2 -> L, 3 -> R
	int next_x, next_y;
	char temp = w[y][x];
	
	if(level < limit){
		//increments the number of nodes expanded
		expanded++;
		
		//calculates the number of nodes that can be generated
		if(y != 0 && w[y-1][x] != '#' && w[y-1][x] != dirt + '0')
			generated++;
		if(y != n - 1 && w[y+1][x] != '#' && w[y+1][x] != dirt + '0')
			generated++;
		if(x != 0 && w[y][x-1] != '#' && w[y][x-1] != dirt + '0')
			generated++;
		if(x != m - 1 && w[y][x+1] != '#' && w[y][x+1] != dirt + '0')
			generated++;
		if(w[y][x] == '*')
			generated++;
		
		//vacuum the dirt
		if(w[y][x] == '*'){
			dirt--;
			expanded++;
			
			//check to see if it is the last one
			if(dirt == 0){
				insertList('V');
				return 1;
			}
		}
			
		//changes the cell value to the number of dirt left
		w[y][x] = dirt + '0';
		
		while(instruction < 4){
			//calculate the next cell to be seen acording to the instruction
			next_y = y;
			next_x = x;

			if(instruction == 0 && y != 0 && w[y-1][x] != '#')
				next_y = y - 1;
			else if(instruction == 1 && y != n - 1 && w[y+1][x] != '#')
				next_y = y + 1;
			else if(instruction == 2 && x != 0 && w[y][x-1] != '#')
				next_x = x - 1;
			else if(instruction == 3 && x != m - 1 && w[y][x+1] != '#')
				next_x = x + 1;
			
			//it just makes sense to pass through the same cell if the number of dirt left in the second time is different than the first	
			if((next_y != y || next_x != x) && w[next_y][next_x] != w[y][x]){
				if(dfs(next_x, next_y, dirt, level + 1, limit) == 1){
					if(instruction == 0)
						insertList('N');
					else if(instruction == 1)
						insertList('S');
					else if(instruction == 2)
						insertList('W');
					else if(instruction == 3)
						insertList('E');
					
					if(temp == '*')
						insertList('V');
						
					return 1;
				}
			}
			
				instruction++;
		}
		
		w[y][x] = temp;
		return 0;
	}
	
	return 0;
}
