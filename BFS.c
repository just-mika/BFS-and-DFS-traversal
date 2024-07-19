List* BFS(Graph* graph, char start[]){
	List* Queue = (List*)malloc(sizeof(List)); //Queue for the traversal
	List* Visited = (List*)malloc(sizeof(List)); //list for visited vertices
	String currVer; //string for ID of current vertex
	List* candidateNodes = (List*)malloc(sizeof(List)); //list for candidates
	
	initializeList(Queue); //initialize the queue
	initializeList(Visited); //initialize visited queue
	addNode(Queue, start); //add the starting vertex
	addNode(Visited, start); //mark starting vertex as visited.
	
	while(!isEmpty(Queue)){
		strcpy(currVer,(Queue)->first->ID); //set a vertex
		node* adj = findVertex(graph,currVer)->first->next; //set first neighbor
		dequeue(Queue); //dequeue the current vertex
		initializeList(candidateNodes); //initialize list of unsorted adjacent nodes of vertex
		
		//check each neighbor of the current vertex if they have been visited
		while(adj != NULL){ 
			if(!isVisited(*Visited, adj->ID)){
				//if visited, add to candidates to sort it later
				addNode(candidateNodes, adj->ID);
			}
			adj = adj->next; //check next neighbor
		}
		//sorts candidates according to its lowest vertex ID, and also adds it to queue to check its neighbors later
		sortCandidates(candidateNodes, Queue, 2);
		if(!isVisited(*Visited, currVer)){
			addNode(Visited, currVer);
		}
	}
	free(Queue); //return allocated memory
	free(candidateNodes); //return allocated memory
	return Visited; //return list containing bfs
}
