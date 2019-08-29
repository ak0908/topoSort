// Yasin Aikebaier
// yaikebai
// PA 4
// 
//-----------------------------------------------------------------------------
// Digraph.c
// Implementation file for Digraph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Digraph.h"

int time = 0;         // global varibale
bool isThereInprogress = false;  // global variable

struct DigraphObj{

	int* arrayInt;    // An array of int value whose jth element indicates whether a vertex
	                  // has been "visited" in the current  search.

	int* arrayTime;   // An array of int vallue whose jth element indicates the finishing time
					  // during a DFS

	int* arrayFinishTime;
	int* arrayDistance; // An array of int value whose jth element indicates the shortest steps
					  // to the source vertex.
	int* arrayIndegree; // An array of int value whose jth element indicstes the indegree of the 
						// jth vertix.
	List* arrayList;  // An array of ListObj* pointer, whose jth element points to the jth 
	                  // ListObj contains the neighbors of vertext j

	List* SSCList; //= (List*)calloc((G->numVertices), sizeof(List));


	

	int numVertices;  // number of vertices(order of the G)
	int numEdges;     // the number of edges in the G(size of the G)

	bool cleanGraph; 
	int numSSC;

}typedef DigraphObj;


// a function to creat a G
Digraph newDigraph(int numVertices){
	Digraph G = (Digraph)malloc(sizeof(DigraphObj));                 // allocating memeory for DigraphObj
	G->numVertices = numVertices;
	G->numSSC = 0;                              // initializing the numVertices filed
	G->numEdges = 0;                         
	G->arrayList = calloc((numVertices + 1), sizeof(List));          // allocating memory for ListObj* pinter
	G->arrayInt = calloc((numVertices + 1), sizeof(int));            // allocating memory for int* pointer
	G->arrayTime = calloc((numVertices + 1), sizeof(int));
	G->arrayDistance = calloc((numVertices + 1), sizeof(int));
	G->arrayFinishTime = calloc((numVertices + 1), sizeof(int));
	G->arrayIndegree = calloc((numVertices + 1), sizeof(int));
	G->SSCList = (List*)calloc((G->numVertices + 1), sizeof(List));

	G->cleanGraph = false;

	G->SSCList[0] = newList();
	for(int i = 1; i < numVertices + 1; i++){
		G->SSCList[i] = newList();
		G->arrayList[i] = newList();
		G->arrayInt[i] = UNVISITED;
		G->arrayDistance[i] = INF;
		G->arrayTime[i] = NIL;
		G->arrayFinishTime[i] = NIL;
		G->arrayIndegree[i] = 0;
	}

	return G;
}

// Frees all dynamic memory associated with its Digraph* argument, and sets
// *pG to NULL.
void freeDigraph(Digraph* pG){
    if((*pG) != NULL && pG != NULL){
        for(int i = 0; i < (*pG)->numVertices + 1; i++){
    	    freeList(&((*pG)->arrayList[i]));
    	    freeList(&((*pG)->SSCList[i]));
    	}

    	free((*pG)->arrayList);
    	free((*pG)->SSCList);
        free((*pG)->arrayInt);  // freeing up the memory occupied by the integer array
        free((*pG)->arrayDistance);
        free((*pG)->arrayFinishTime);
        free((*pG)->arrayIndegree);
        free((*pG)->arrayTime);

        free(*pG);

        *pG = NULL;
    }
}


/*** Access functions ***/
// Returns the order of G, the number of vertices in G.
int getOrder(Digraph G){
	return G->numVertices;
}

// Returns the size of G, the number of edges in G.
int getSize(Digraph G){
	return G->numEdges;
}

// return true if v is legal vertext, otherwise false
bool isLegalVertex(Digraph G, int v){
	if(v > 0 && v <= G->numVertices){
		return true;
	}else
		return false;
}

bool doesEdgeExist(Digraph G, int u, int v){

	if(doesNodeExist(G->arrayList[u], v)) return true;

	return false;
}

// Returns the number of neighbors that vertex v has in G. Returns -1 if v is not a legal vertex.
int GetOutDegree(Digraph G, int v){
	if(v <= 0 || v > G->numVertices){
		// printf("\nDigraph error: calling GetOutDegree() on invalid vertex.....\n");
		return -1;
	}

	return length(G->arrayList[v]);
}

// Returns a list that has all the vertices that are neighbors of u. There is no input operation
// that corresponds to getNeighbors.
List getNeighbors(Digraph G, int v){
	if(v <= 0 || v > G->numVertices){
	    printf("\nDigraph error: calling getNeighbor() on invalid vertex.....\n");
	}

	return G->arrayList[v];
}



/*** Manipulation procedures ***/
// Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t
// already exist. If the edge does already exist, does nothing. Used when edges are entered.
// Returns 0 if u and v are legal vertices, otherwise returns 1.
int addEdge(Digraph G, int u, int v){
	if(isLegalVertex(G, u) && isLegalVertex(G, v)){
		if(!doesEdgeExist(G, u, v)){
			prepend(G->arrayList[u], v);
			insertSort(G->arrayList[u]);
			G->numEdges ++;
			G->arrayIndegree[v] ++;
			G->cleanGraph = false;
			return 0;
		}
		return 1;
	}
	return -1;
}

int deleteEdge(Digraph G, int u, int v){
	if(doesEdgeExist(G, u, v)){
		Node toBeDeleted = giveMeNodeIfIGiveYouData(G->arrayList[u], v);
		detachNode(G->arrayList[u], toBeDeleted);
		G->numEdges --;
		G->arrayIndegree[v] --;
		G->cleanGraph = false;
		return 0;
	}
	if(isLegalVertex(G, u) && isLegalVertex(G, v)){
		return 1;
	}

	return -1;
}

// Marks all vertices of the graph as UNVISITED.
void unvisitAll(Digraph G){
    for(int i = 1; i < G->numVertices + 1; i++){
    	G->arrayInt[i] = UNVISITED;
    }
}

void INFAll(Digraph G){
    for(int i = 1; i < G->numVertices + 1; i++){
    	G->arrayDistance[i] = INF;
    }
}

void resetTimeAll(Digraph G){
    for(int i = 1; i < G->numVertices + 1; i++){
    	G->arrayTime[i] = NIL;
    	G->arrayFinishTime[i] = NIL;
    }
}

// Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE.
int getMark(Digraph G, int u){
	return G->arrayInt[u];
}

// Sets the mark for vertex u to be theMark.
// theMark must be UNVISITED, INPROGRESS or ALLDONE.
void setMark(Digraph G, int u, int theMark){
	if(theMark == UNVISITED || theMark == INPROGRESS || theMark == ALLDONE){
		G->arrayInt[u] = theMark;
	}
	else{
		printf("\nDigraph error: the Mark is invalid\n");
	}
}

// Described below; returns FOUND or NOTFOUND, which are (different) constants.
int PathExistsRecursive(Digraph G, int w, int v){
	if(w == v) return FOUND;

	int theMark;
	int theFoundValue = false;
    setMark(G, w, INPROGRESS);

	for(int i = 0; i < GetOutDegree(G,w); i ++){
		theMark = getMark(G, dataValueAtIndex(getNeighbors(G, w), i));
		
		if(theMark == UNVISITED){
			theFoundValue = PathExistsRecursive(G, dataValueAtIndex(getNeighbors(G, w), i), v);
		}
		if(theFoundValue == FOUND){
			return FOUND;
		}
	}

	// Finished processing all of x's neighbors without finding  v
	setMark(G, w, ALLDONE);
	return(NOTFOUND);
}

void printDigraph(FILE* out, Digraph G){
	int counter = G->numEdges;
	fprintf(out, "%d, ", G->numVertices);
	for(int i = 1; i < G->numVertices + 1; i++){
		for(int j = 0; j < GetOutDegree(G, i); j++){
			fprintf(out, "%d %d", i, dataValueAtIndex(G->arrayList[i], j));
			counter --;
			if (counter != 0) fprintf(out, ", ");
			
		}
	}
}

// Outputs the distance between vertices u and v if there is a directed path between them in the
// digraph. Otherwise, outputs INF
void distance(FILE* out, Digraph G, int u, int v){
	BFS(G, u);
	if(G->arrayDistance[v] == INF){
		fprintf(out, "%s\n", "INF");
	}
	else{
		fprintf(out, "%d\n", G->arrayDistance[v]);
	}
	

	unvisitAll(G);
	INFAll(G);
}

void BFS(Digraph G, int s){
	unvisitAll(G);
	INFAll(G);

	G->arrayInt[s] = INPROGRESS;
	G->arrayDistance[s] = 0;
	List Q = newList();
	prepend(Q, s);          // enqueue
	while(length(Q) != 0){
		int u = backValue(Q);
		deleteBack(Q);      // dequeue
		for(int i = 0; i < length(G->arrayList[u]); i++){
			int v = dataValueAtIndex(G->arrayList[u], i);
			if(G->arrayInt[v] == UNVISITED){
				setMark(G, v, INPROGRESS);
				G->arrayDistance[v] = (G->arrayDistance[u]) + 1;
				prepend(Q, v);
			}
		}
		setMark(G, u, ALLDONE);
	}
	freeList(&Q);
}

int DFSforTranspose(Digraph GT, List S, List* SSCList){
	unvisitAll(GT);
	resetTimeAll(GT);
	isThereInprogress = false;


	int numSSC = 0;

	time = 0;
	while(length(S)){
		if(GT->arrayInt[frontValue(S)] == UNVISITED){
			DFS_visit(GT, frontValue(S), SSCList[numSSC]);
			numSSC ++;
		}
		deleteFront(S);
	}

	freeList(&S);

	return numSSC;	
}

List DFS(Digraph G){
	unvisitAll(G);
	resetTimeAll(G);
	isThereInprogress = false;

	List S = newList();

	time = 0;
	for(int i = 1; i <= getOrder(G); i ++){
		if(G->arrayInt[i] == UNVISITED){
			DFS_visit(G, i, S);
		}
	}

	return S;
}

void DFS_visit(Digraph G, int u, List S){
	time ++;
	G->arrayTime[u] = time;
	G->arrayInt[u] = INPROGRESS;
	for(int i = 0; i < length(G->arrayList[u]); i++){
		int v = dataValueAtIndex(G->arrayList[u], i);
		if(G->arrayInt[v] == INPROGRESS) isThereInprogress = true;
		if(G->arrayInt[v] == UNVISITED){
			DFS_visit(G, v, S);
		}
	} 
	G->arrayInt[u] = ALLDONE;
	prepend(S, u);
	time ++;
	G->arrayFinishTime[u] = time;
}


// Outputs YES if the digraph is acyclic. Otherwise, outputs NO.
void acyclic(FILE* out, Digraph G){
	bool thereIsNoZoroIndegree = true;
	for(int i = 1; i <= getOrder(G); i++){
		if(G->arrayIndegree[i] == 0) thereIsNoZoroIndegree = false;
	}
	if(thereIsNoZoroIndegree){
		fprintf(out, "%s\n", "NO");
		return;
	}


	List S = DFS(G);
	if(!isThereInprogress){
		fprintf(out, "%s\n", "YES");
	}
	else{
		fprintf(out, "%s\n", "NO");
	}

	freeList(&S);
	
}

// Outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.
void topoSort(FILE* out, Digraph G){
	List S = DFS(G);
	if(isThereInprogress){
		fprintf(out, "%s\n", "IMPOSSIBLE");
		freeList(&S);
		return;
	}

	printList(out, S);
	freeList(&S);
}

Digraph transpose(Digraph G){
	Digraph GT= newDigraph(G->numVertices);
	for(int i = 1; i <= G->numVertices; i ++){
		for(int j = 0; j < length(G->arrayList[i]); j ++){
			addEdge(GT, dataValueAtIndex(G->arrayList[i], j), i);
		}
	}

	return GT;
}

int GetCountSCC(Digraph G){
	if(G->cleanGraph) return G->numSSC;

	// if the graph is modified, do the follow

	Digraph GT = transpose(G);
	List* SSCList = G->SSCList; 
	for(int i = 0; i < G->numSSC; i++) clear(G->SSCList[i]);
	G->numSSC = DFSforTranspose(GT, DFS(G), SSCList);

    freeDigraph(&GT);
    G->cleanGraph = true;

    return G->numSSC;

}

int GetNumSCCVertices(Digraph G, int v){
	int ret;

	if(G->cleanGraph){
		for(int i = 0; i < G->numSSC; i++){
			if(giveMeNodeIfIGiveYouData(G->SSCList[i], v) != NULL){
				ret =  length(G->SSCList[i]);
			}
		}	
		return ret;
	}

	// if the graph is modifided do the follow

	Digraph GT = transpose(G);
	List* SSCList = G->SSCList; //(List*)calloc((G->numVertices), sizeof(List));
	for(int i = 0; i < G->numSSC; i++) clear(G->SSCList[i]);

	G->numSSC = DFSforTranspose(GT, DFS(G), SSCList);

	for(int i = 0; i < G->numSSC; i++){
		if(giveMeNodeIfIGiveYouData(SSCList[i], v) != NULL){
			ret =  length(SSCList[i]);
		}
	}

    freeDigraph(&GT);
    G->cleanGraph = true;

    return ret;
	
}

void InSameSCC(FILE* out, Digraph G, int v, int w){
	if(G->cleanGraph){
		for(int i = 0; i < G->numSSC; i++){
			if(giveMeNodeIfIGiveYouData(G->SSCList[i], v) != NULL){
				if(giveMeNodeIfIGiveYouData(G->SSCList[i], w) != NULL){
					fprintf(out, "%s\n", "YES");
					goto weAreDone;
				}
			}
		}

		fprintf(out, "%s\n", "NO");
		
		weAreDone:
		return;
	}

	// if the graph is modified do the follow

	Digraph GT = transpose(G);

	List* SSCList = G->SSCList; //(List*)calloc((G->numVertices), sizeof(List));
	for(int i = 0; i < G->numSSC; i++) clear(G->SSCList[i]);
	G->numSSC = DFSforTranspose(GT, DFS(G), SSCList);

	for(int i = 0; i < G->numSSC; i++){
		if(giveMeNodeIfIGiveYouData(SSCList[i], v) != NULL){
			if(giveMeNodeIfIGiveYouData(SSCList[i], w) != NULL){
				fprintf(out, "%s\n", "YES");
				goto freeTheMemory;
			}
		}
	}

	fprintf(out, "%s\n", "NO");

	freeTheMemory:
    freeDigraph(&GT);
    G->cleanGraph = true;
}

void insertSort(List L){

    Node Nj, Ni; // this two pointer will act as i and j

    int key;

    for(Nj = getNextNode(getFront(L)); Nj != NULL; Nj = getNextNode(Nj)){

        key = getValue(Nj);

        // insert L[j] into the sorted L[1....j-1]
        Ni = getPrevNode(Nj);    

        while(Ni != NULL && getValue(Ni) > key){
            changeData(getNextNode(Ni), getValue(Ni));  //Ni->next->data = Ni->data;
            Ni = getPrevNode(Ni); 
        }

        if(Ni == NULL) changeData(getFront(L), key); // this is the situation that i index jump off the edge
        else changeData(getNextNode(Ni), key); //Ni->next->data = key;
    }
}



