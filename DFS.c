List* DFS(Graph graph, String start){
    List* Stack = (List*)malloc(sizeof(List)); //Stack for traversal
    List* Visited = (List*)malloc(sizeof(List)); //Stack for visited vertices
    String currVer; //string for ID of current vertex
    List* candidateNodes = (List*)malloc(sizeof(List)); //placeholder for candidates before sort
    int index = 1;

    initializeList(Stack);
    initializeList(Visited);
    //put root in stack
    addNode(Stack, getOriginalCase(graph, start));

    while(!isEmpty(Stack)){
        strcpy(currVer, Stack->last->ID);
        pop(Stack);
        if (!isVisited(*Visited, currVer)) {
            addNode(Visited, currVer);
        }
        node* child = findVertex(&graph, currVer)->first->next; //get root adjacent
        initializeList(candidateNodes);
        while(child != NULL){
            if(!isVisited(*Visited, child->ID)){
                addNode(candidateNodes, child->ID);
            }
            child = child->next;
        }
        sortCandidates(candidateNodes, Stack);
    }

    
free(Stack);
free(candidateNodes);
return Visited;
}
