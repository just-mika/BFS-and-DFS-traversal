#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.c"
#include "BFS.c"
#include "DFS.c"

void test1(Graph* graph);
void test2(Graph* graph);


int main(){
	FILE* fInput;
	FILE* fOutput;
	String fileName;
	int notEnd = 1;
	int vertexCount;
	String temp;
	String startVertex;
	int hasStartVertex = 0;
	Graph* graph;
	List* bfs;
	List* dfs;

	printf("Input filename: ");
	scanf("%s", fileName);

	fInput = fopen(fileName, "r");
	if(fInput == NULL){
		printf("%s not found.", fileName);
	}else{
		printf("Input start vertex for traversal: ");
		scanf("%s", startVertex);
		fscanf(fInput, "%d\n", &vertexCount);
		graph = createGraph(vertexCount);
		for(int i = 0; i < graph->nVertices; i++){
			fscanf(fInput,"%s", temp);
			if(strcasecmp(temp, startVertex) == 0){
				hasStartVertex = 1;
			}
			addVertex(graph, temp);
			while(notEnd){
				fscanf(fInput, "%s", temp);
				if(strcmp(temp, "-1") != 0){
					addNode(&graph->vertices[i], temp);
				}else{
					notEnd = 0;
				}
			}
			notEnd = 1;
		}
		if(hasStartVertex == 0){
			printf("vertex not found");
		}else{//put in traversals.txt
			fOutput = fopen("TRAVERSALS.TXT", "w");
			if(fOutput == NULL){
				printf("error in creating output file");
			}else{
				for(int i = 0; i < graph->nVertices; i++){ //prints the vertices and degree in file
					fprintf(fOutput, "%s\t%d\n", graph->vertices[i].first->ID, countDegrees(&graph->vertices[i]));	
				}
				fprintf(fOutput, "\n");
				bfs = BFS(graph, startVertex);
				node* temp = bfs->first;
				while(temp != NULL){
					fprintf(fOutput, "%s ", temp->ID);
					temp = temp->next;
				}
				fprintf(fOutput, "\n\n");
				dfs = DFS(*graph, startVertex);
				temp = dfs->first;
				while(temp != NULL){
					fprintf(fOutput, "%s ", temp->ID);
					temp = temp->next;
				}
			}
		}
	}

	fclose(fInput);
	fclose(fOutput);
	return 0;
}


	/* TEST 1 (check graph in specs)
	Graph* graph = createGraph(4);
	test1(graph);
	*/
	
	/*TEST2 (graph from: https://visualgo.net/en/dfsbfs)
		(i put the graph in our github repo.)
		NOTE: dont uncomment both tests at the same time.
	Graph* graph = createGraph(9);
	test2(graph);
	*/
		
	//printGraph(graph); //(uncomment to check the adj list)
	/*
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
	*/


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
