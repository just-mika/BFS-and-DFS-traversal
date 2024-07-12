#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.c"
#include "BFS.c"
//#include "DFS.c"

void test1(Graph* graph);
void test2(Graph* graph);

int main(){
	/* TEST 1 (check graph in specs) */
	Graph* graph = createGraph(4);
	test1(graph);
	
	/*TEST2 (graph from: https://visualgo.net/en/dfsbfs)
		(i put the graph in our github repo.)
		NOTE: dont uncomment both tests at the same time.
	Graph* graph = createGraph(9);
	test2(graph);
	*/
		
	//printGraph(graph); //(uncomment to check the adj list)
	if(!isGraphEmpty(graph)){
		String start;
		
		listVertices(graph);
		printf("Input start vertex for the traversal: ");
		scanf("%s", start);
		
		if(findVertex(graph, start) != NULL){
			BFS(graph, start);
		}
		else
			printf("Vertex %s not found.", start);
	}
	return 0;
}

void test1(Graph* graph){
	addVertex(graph, "Bruce");
	addVertex(graph, "Clark");
	addVertex(graph, "Diana");
	addVertex(graph, "Hal");
	
	addEdge(graph, "Bruce", "Diana");
	addEdge(graph, "Clark", "Diana");
	addEdge(graph, "Clark", "Hal");
	addEdge(graph, "Hal", "Diana");
}

void test2(Graph* graph){
	addVertex(graph, "0");
	addVertex(graph, "1");
	addVertex(graph, "2");
	addVertex(graph, "3");
	addVertex(graph, "4");
	addVertex(graph, "5");
	addVertex(graph, "6");
	addVertex(graph, "7");
	addVertex(graph, "8");
	
	addEdge(graph, "0", "1");
	addEdge(graph, "1", "2");
	addEdge(graph, "1", "3");
	addEdge(graph, "2", "3");
	addEdge(graph, "3", "4");
	addEdge(graph, "6", "7");
	addEdge(graph, "6", "8");
}