typedef char String[255];

//struct for the node
typedef struct nodeTag {
	String ID; //ID of the node
	struct nodeTag *next; //recursion for the next node
} node;

//struct for the list of nodes (Queue implementation)
typedef struct {
	node* first; //pointer to the first (head) node
	node* last; //pointer to the last (tail) node
} List; 

//struct for the graph
typedef struct {
	int nVertices; //number of vertices
	List* vertices; //adjacency list
} Graph;

//operations for the list/queue/stack
void initializeList(List* list);
int isVisited(List visited, char ID[]);
void printList(List list);
int isEmpty(List* list);
node* createNode(char ID[]);
void addNode(List* list, char ID[]);
void dequeue(List* list);
void pop(List * stack);
void sortCandidates(List* candidates, List* stack);

//operations for graph
int isGraphEmpty(Graph* graph);
Graph* createGraph(int vertices);
void addVertex(Graph* graph, char ID[]);
List* findVertex(Graph* graph, char ID[]);
void addEdge(Graph* graph, char ID1[], char ID2[]);
void listVertices(Graph* graph);
void printGraph(Graph* graph);
int countDegrees(List* list);
char* getOriginalCase(Graph graph, char ID[]);
