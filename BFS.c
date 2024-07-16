List* BFS(Graph* graph, char start[]){
	List* Queue = (List*)malloc(sizeof(List)); //Queue for the traversal
	List* Visited = (List*)malloc(sizeof(List)); //Queue for visited vertices
	String currVer; //string for ID of current vertex
	
	initializeList(Queue); //initialize the queue
	initializeList(Visited); //initialize visited queue
	addNode(Queue, start); //add the starting vertex
	addNode(Visited, start); //mark starting vertex as visited.
	
	while(!isEmpty(Queue)){
		strcpy(currVer,(Queue)->first->ID); //set a vertex
		node* adj = findVertex(graph,currVer)->first->next; //set first neighbor
		dequeue(Queue); //dequeue the current vertex
		//check each neighbor of the current vertex if they have been visited
		while(adj != NULL){ 
			if(!isVisited(*Visited, adj->ID)){
				//if visited, add to queue to check its neighbors later
				addNode(Queue, adj->ID);
				addNode(Visited, adj->ID); //add said node to visited
			}
			adj = adj->next; //check next neighbor
		}
	}
	free(Queue); //return allocated memory
	return Visited; //return list containing bfs
}
