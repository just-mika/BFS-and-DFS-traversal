#include <ctype.h>
#include "graph.h"

//for initializing a list
void initializeList(List* list){
	list->first = NULL;
	list->last = NULL;
}

//checks if a vertex is visited
int isVisited(List visited, char ID[]){
	node* temp = visited.first;
	while(temp != NULL){
		if(strcasecmp(temp->ID, ID) == 0) //strcasecmp for incase-sensitive check
			return 1;
		else
			temp = temp->next;
	}
	return 0;
}

//prints the queue/list
void printList(List list) {
	node* temp = list.first;
	printf("\n(should be in TRAVERSAL.TXT)\n");
	while(temp != NULL) {
		printf("%s ", temp->ID);
		temp = temp->next;  
	}
	printf("\n");
}

//checks if a list is empty
int isEmpty(List* list){
    return (list->first) == NULL;
}

//creates a node
node* createNode(char ID[]){
	node* newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->ID, ID);
	newNode->next = NULL;
	
	return newNode;
}

//adds a node in a list (aka enqueue)
void addNode(List* list, char ID[]){
	node* temp = createNode(ID);
	if(isEmpty(list)){
		list->last = temp;
		list->first = temp;
	}
	else {
		list->last->next = temp;
		list->last = temp;
	}
}

//removes first node in a queue
void dequeue(List* list) {
    if (list->first == NULL) {
        printf("QUEUE EMPTY\n");
    }
    else {
    	node* temp = list->first;
	    list->first = list->first->next;
	    
	    if (list->first == NULL)
	        list->last = NULL;
	    free(temp);
	}
}

//checks if a graph is empty
int isGraphEmpty(Graph* graph){
	return (graph->vertices[0].first) == NULL;
}

//creates a graph
Graph* createGraph(int vertices){
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->nVertices = vertices;
	graph->vertices = (List*)malloc(vertices * sizeof(List)); //allocate memory for adj list
	
	for(int i = 0; i < vertices; i++) //initialize the adjacency lsit
		initializeList(&(graph->vertices[i]));
	return graph;
}

//adds a vertex in the graph
void addVertex(Graph* graph, char ID[]){
	int i = 0;
	while(graph->vertices[i].first != NULL)
		i++;
	addNode(&(graph->vertices[i]), ID);
}

//finds a vertex in the graph with given ID. if found, it returns the vertex itself and its list of neighbors.
List* findVertex(Graph* graph, char ID[]){
	for(int i = 0; i < graph->nVertices; i++){
		node* temp = graph->vertices[i].first;
		if(strcasecmp(temp->ID, ID) == 0)
			return &(graph->vertices[i]);
	}
	return NULL;
}

//adds an edge/connects two vertices (undirected)
void addEdge(Graph* graph, char ID1[], char ID2[]){
	List* vertex1 = findVertex(graph, ID1);
	List* vertex2 = findVertex(graph, ID2);
	
	if(vertex1 != NULL && vertex2 != NULL){
		addNode(vertex1, ID2);
		addNode(vertex2, ID1);
	}
}

//lists all vertices and its number of neighbors.
void listVertices(Graph* graph){
	int ctr;
	printf("(should be in TRAVERSAL.TXT)\n");
	for(int i = 0;i < graph->nVertices; i++){
		ctr = 0;
		node* temp = graph->vertices[i].first;
		String ID;
		strcpy(ID, temp->ID);
		while(temp->next != NULL){
			ctr++;
			temp = temp->next;
		}
		printf("%s\t%d\n", ID, ctr);
	}
}

/* for debug*/
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->nVertices; i++) {
        node* temp = graph->vertices[i].first;
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%s -> ", temp->ID);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

//count degrees of a vertex
int countDegrees(List* list){
	int size = 0;
	node* temp = list->first;
	while(temp != NULL){
		temp = temp->next;
		size++;
	}
	return size-1;
}

//for retaining the same upper lower case in input to output
char* getOriginalCase(Graph graph, char ID[]){
	int i;
	for(i = 0; i < graph.nVertices; i++){
		if(strcasecmp(ID, graph.vertices[i].first->ID) == 0){
			return graph.vertices[i].first->ID;
		}
	}
	return NULL;
}

//pop last node in stack for dfs
void pop(List* list){
    node* temp = list->first;
    if(list->first == NULL){
        printf("LIST IS EMPTY\n");
    } else if (list->first == list->last) {
        free(list->first);
        list->first = NULL;
        list->last = NULL;
    } else{
        while(temp->next != list->last){
            temp = temp->next;
        }
        free(list->last);
        list->last = temp;
        list->last->next = NULL;
    }
}

//sort candidate nodes into descending/ascending order then store it in stack/queue
void sortCandidates(List* candidates, List* list, int traversal){
	node* temp1;
	node* last = NULL;
    	int swapped = 0;

	//sorts descending for DFS
	if(traversal == 1){
		if(candidates->first != NULL){//bubble sort to descending
			do {
				swapped = 0;
				temp1 = candidates->first;

				while (temp1->next != last) {
					if (strcmp(temp1->ID, temp1->next->ID) < 0) {
						String tempID;
						strcpy(tempID, temp1->ID);
						strcpy(temp1->ID, temp1->next->ID);
						strcpy(temp1->next->ID, tempID);
						swapped = 1;
					}
					temp1 = temp1->next;
				}
				last = temp1;
			} while (swapped);
		}

		//copy sorted values to stack list
		temp1 = candidates->first;
		while(temp1 != NULL){
			addNode(list, temp1->ID);
			temp1 = temp1->next;
		}
	}else{ //sort in ascending for BFS
		if(candidates->first != NULL){//bubble sort to descending
			do {
				swapped = 0;
				temp1 = candidates->first;

				while (temp1->next != last) {
					if (strcmp(temp1->ID, temp1->next->ID) > 0) {
						String tempID;
						strcpy(tempID, temp1->ID);
						strcpy(temp1->ID, temp1->next->ID);
						strcpy(temp1->next->ID, tempID);
						swapped = 1;
					}
					temp1 = temp1->next;
				}
				last = temp1;
			} while (swapped);
		}

		//copy sorted values to queue list
		temp1 = candidates->first;
		while(temp1 != NULL){
			addNode(list, temp1->ID);
			temp1 = temp1->next;
		}
	}

}
