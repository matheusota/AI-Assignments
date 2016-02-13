#include "functions.h"

//check adjacents vertices to see if there is repeated color
bool checkVertices(int u){
	adj_list adjacents;
	
	for(adjacents = graph[u].head -> next; adjacents != NULL; adjacents = adjacents -> next){
		if(graph[u].color == graph[adjacents -> index].color)
			return false;
	}
	
	return true;
}

//find the next variable to try to assign
int findValue(int mode){
	int i, j, smaller, next;
	bool flag;
	
	smaller = 99999;
	flag = true;
	next = -1;
	
	for(i = 0; i < n; i++){
		if(graph[i].size < smaller && graph[i].color == -1){
			
			//check restrictions
			if(mode > 0){
				flag = false;
				
				for(j = 0; j < k; j++){
					if(graph[i].restrictions[j] == 0)
						flag = true;
				}
			}
			
			//returns first possible variable
			if(flag && mode < 2)
				return i;
			
			//find most constrained variable if mode is mcv
			else if(flag){
				next = i;
				smaller = graph[i].size;
			}
		}
	}
	
	return next;
}

//try coloring the graph using dfs
// mode 0, simple dfs
// mode 1, dfs with forward checking
// mode 2, dfs with most constrained value
bool dfs(int u, int color, int n_color, int mode){
	adj_list adjacents = graph[u].head -> next;
	int i, next_var;
	bool r;
	
	nodes++;
	
	graph[u].color = color;
	n_color++;
	
	//simple checking
	if(mode == 0 && !checkVertices(u)){
		graph[u].color = -1;//uncolor it
		return false;
	}
	
	//check if colored every vertex already
	if(n_color == n)
		return true;
		
	//forward checking
	else if(mode > 0){
		for(adjacents = graph[u].head -> next; adjacents != NULL; adjacents = adjacents -> next){
			if(graph[adjacents -> index].restrictions[color] == 0)
				graph[adjacents -> index].size--;
			graph[adjacents -> index].restrictions[color]++;
		}
	}
	
	//branch to next node
	next_var = findValue(mode);
	
	//no possible variable
	if(next_var == -1)
		return false;
		
	for(i = 0; i < k; i++){
		if(graph[next_var].restrictions[i] == 0 && dfs(next_var, i, n_color, mode))
			return true;
	}
	
	//reverse forward checking
	if(mode > 0){
		for(adjacents = graph[u].head -> next; adjacents != NULL; adjacents = adjacents -> next){
			graph[adjacents -> index].restrictions[color]--;
			if(graph[adjacents -> index].restrictions[color] == 0)
				graph[adjacents -> index].size++;
		}
	}
	
	return false;
}
