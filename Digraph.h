// Yasin Aikebaier
// yaikebai
// PA 4
// 
//-----------------------------------------------------------------------------
// Digraph.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include "List.h"

#define UNVISITED 2
#define INPROGRESS 3
#define ALLDONE 4
#define FOUND 1
#define NOTFOUND 0
#define INF 1000000
#define NIL -1


// Exported type --------------------------------------------------
// change the pointer data type(DigraphObj*) to Digraph
typedef struct DigraphObj* Digraph;

/*** Constructors-Destructors ***/
Digraph newDigraph(int numVertices);
// Returns a Digraph that points to a newly created DigraphObj representing a graph which has
// n vertices and no edges.
void freeDigraph(Digraph* pG);
// Frees all dynamic memory associated with its Digraph* argument, and sets
// *pG to NULL.


/*** Access functions ***/
int getOrder(Digraph G);
// Returns the order of G, the number of vertices in G.
int getSize(Digraph G);
// Returns the size of G, the number of edges in G.
int GetOutDegree(Digraph G, int v);
// Returns the number of neighbors that vertex v has in G. Returns -1 if v is not a legal vertex.
List getNeighbors(Digraph G, int v);
// Returns a list that has all the vertices that are neighbors of u. There is no input operation
// that corresponds to getNeighbors.


/*** Manipulation procedures ***/
int addEdge(Digraph G, int u, int v);
// Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t
// already exist. If the edge does already exist, does nothing. Used when edges are entered.
// Returns 0 if u and v are legal vertices, otherwise returns -1.
void unvisitAll(Digraph G);
// Marks all vertices of the graph as UNVISITED.
void resetTimeAll(Digraph G);
void INFAll(Digraph G);

int getMark(Digraph G, int u);
// Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE.
void setMark(Digraph G, int u, int theMark);
// Sets the mark for vertex u to be theMark.
// theMark must be UNVISITED, INPROGRESS or ALLDONE.
int PathExistsRecursive(Digraph G, int w, int v);
// Described below; returns FOUND or NOTFOUND, which are (different) constants.
int deleteEdge(Digraph G, int u, int v);


/*** Other operations ***/
void printDigraph(FILE* out, Digraph G);
// Prints the Digraph G in the same format as an input line, so all that a client need to do is a single
// call to PrintDigraph(). But it should not print out an edge twice. Achieve this by only printing
// the edge for {j, k} when j < k.

bool isLegalVertex(Digraph G, int v);  // This is my own helper function to check if a vertex exists in the graph

void distance(FILE* out, Digraph G, int u, int v);
// Outputs the distance between vertices u and v if there is a directed path between them in the
// digraph. Otherwise, outputs INF
void acyclic(FILE* out, Digraph G);
// Outputs YES if the digraph is acyclic. Otherwise, outputs NO.
void topoSort(FILE* out, Digraph G);
// Outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.
void BFS(Digraph G, int s);
List DFS(Digraph G);
void DFS_visit(Digraph G, int u, List S);

int GetCountSCC(Digraph G);
int GetNumSCCVertices(Digraph G, int v);
void InSameSCC(FILE* out, Digraph G, int v, int w);

void insertSort(List L);

#endif 