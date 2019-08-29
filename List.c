// Yasin Aikebaier
// yaikebai
// PA 4
// 
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------
// Node type
struct NodeObj{
	struct NodeObj* next; // pointer to next NodeObj
	struct NodeObj* prev; // pointer to prev NodeObj
	int data;
}typedef NodeObj;

// list struct
struct ListObj{
	Node front;
	Node back;
	int length;

}typedef ListObj;



// Constructions-Destructions -------------------------------

// newNode()
// Returns reference to new Node Object. initializes the next and prev pointers and data
Node newNode(int data){
	Node N = (Node)malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;

	return N;
}

// freeNode()
// frees heap memory pointed to by pN
// sets *pN to NULL
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}


// newList()
// return a List which points to new empty L object
List newList(void){        
	List L = (List)malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->length = 0;
	return L;
}


// freeList()
// frees all heap memory associated with its List* argument,
// and sets  pL to NULL
void freeList(List* pL){
	if (*pL != NULL && pL != NULL){
		while((*pL)->length != 0){
			deleteBack(*pL);
		}
		free(*pL);
		*pL = NULL;	


	}

}


// Access functions -----------------------------------------

// Returns the number of Ns in this List.
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on Null List reference\n");
		exit(1);
	}
	return L->length;
}

// Returns the integer in the front Node.
// Precondition: L has at least one Node on it.
int frontValue(List L){
	if(L == NULL){
		printf("List Error: calling frontValue() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling frontValue() on an empty list\n");
		exit(1);
	}

	return L->front->data;
}

// Returns the integer in the back Node.
// Precondition: L has at leas one Node on it.
int backValue(List L){
	if(L == NULL){
		printf("List Error: calling backValue() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling backValue() on a empty list\n"); 
		exit(1);
	}

	return L->back->data;
}

// Returns the integer in Node N.
// Precondition: N is not NULL
int getValue(Node N){
	if(N == NULL){
		printf("Error: calling getValue() on a Null Node reference\n");
		exit(1);
	}

	return N->data;
}

// Returns 1 if List A and ListB are the same integer
// sequence, otherwise returns 0
int equals(List A, List B){

	if(A == NULL || B == NULL){
		printf("List Error: calling equals on Null list reference\n");
		exit(1);
	}

	int returnValue = 0;
	Node Na = NULL;
	Node Nb = NULL;

	returnValue = (A->length == B->length);

	if(!returnValue) return returnValue;

	while(returnValue && (Na != NULL)){
		returnValue = (Na->data == Nb->data);
		Na = Na->next;
		Nb = Nb->next;
	}

	return returnValue;
}


// Mainipulation Procedures ------------------------------------

// Rests this List to the empty state
void clear(List L){

	if(L == NULL){
		printf("List Error: calling prepend() on Null List reference\n");
		exit(1);
	}

	while(L->length > 0){
		deleteBack(L);
	}
}

// If List is non-empty, returns the front Node, without
// changing the List. otherwise, does nothing
Node getFront(List L){

	if(L == NULL){
		printf("List Error: calling getFront() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling getFront() on an empty List\n");
		exit(1);
	}

	return L->front;
}

// If List is non-empty, returns the back Node, without
// changing the List. otherwise, does nothing
Node getBack(List L){

	if(L == NULL){
		printf("List Error: calling getBack() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling getBack() on an empty List\n");
		exit(1);
	}

	return L->back;
}

// Without change the List that N is on, returns the 
// Node that is previous to Node N on its List. if 
// there is no previous Node, returns NULL.
Node getPrevNode(Node N){
	return N->prev;
}

// Without change the List that N is on, returns the 
// Node that is next after Node N on its List. if 
// there is no next Node, returns NULL.
Node getNextNode(Node N){
	return N->next;
}

// Insert a new Node into list L before the front
// Node. If List is empty, makes that new Node the 
// the only node on the list.
void prepend(List L, int data){
	

	if(L == NULL){
		printf("List Error: calling prepend() on Null List reference\n");
		exit(1);
	}

	Node N = newNode(data);


	if(L->length == 0){

		L->front = N;
		L->back = N;
	}
	else{
		N->next = L->front;
		L->front->prev= N;
		L->front = N;
	}

	L->length ++;
}

// Insert a new Node into List L after the back
// Node that has data as its value. if List is empty
// makes that new Node the only Node on the list.

void append(List L, int data){
	Node N  = newNode(data);

	if(L == NULL){
		printf("List Error: calling prepend() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		L->front = N;
		L->back = N;
	}	
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = N; 
	}

	L->length ++;
}

// Inserts a new Node into Node N's list berfor Node N that has data
// as its value. Assume that Node N is on List L. if node N is the front
// of list L, then N becomes the new front. 
// Precondition: Node N is not NULL
void insertBefore(List L, Node N, int data){

	if(L == NULL){
		printf("List Error: calling insertBefore() on Null List reference\n");
		exit(1);
	}

	Node Nnew = (Node)malloc(sizeof(NodeObj));
	Nnew->data = data;

	if(N->prev == NULL){
		N->prev = Nnew;
		Nnew->next = N;
		L->front = Nnew;
		Nnew->prev = NULL; // shifts the front pointer one unit left 
	}
	else{
		N->prev->next = Nnew;
		Nnew->prev = N->prev;
		N->prev = Nnew;
		Nnew->next= N;

	}

	L->length ++;
}

// Inserts a new Node into Node N's list after Node N that has data
// as its value. Assume that Node N is on List L. if node N is the back
// of list L, then N becomes the new back. 
// Precondition: Node N is not NULL
void insertAfter(List L, Node N, int data){

	if(L == NULL){
		printf("List Error: calling insertAfter() on Null List reference\n");
		exit(1);
	}

	Node Nnew = (Node)malloc(sizeof(NodeObj));
	Nnew->data = data;

	if(N->next == NULL){
		N->next = Nnew;
		Nnew->prev = N;
		L->back =  Nnew;   
		Nnew->next = NULL; // shifts the back pointer one unit right		
	}
	else{
		N->next->prev = Nnew;
		Nnew->next = N->next;
		N->next = Nnew;
		Nnew->prev = N;
	}

	L->length ++;

}



// Deletes the front node in List L.
// Precondition: L has at least one Node on it
void deleteFront(List L){

	if(L == NULL){
		printf("List Error: calling deleteFront() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}

	Node N = L->front;  // N points to the NodeObj to be deleted

	if(L->length > 1){
		L->front = N->next; // the front pointer shifts to the second NodeObj
		L->front->prev = NULL;		
	}
	else{
		L->front = L->back = NULL;
	}

	L->length --;

	freeNode(&N);
}

// Deletes the back Node in List L.
// Precondition: L has at least one Node on it
void deleteBack(List L){

	if(L == NULL){
		printf("List Error: calling deleteBack() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(1);
	}

	Node N = L->back; // N points to the NodeObj to bedeleted

	if(L->length > 1){
		L->back = N->prev; // the back pointer shifts back one NodeObj
		L->back->next = NULL;
	}
	else{
		L->back= L->front = NULL;
	}

	L->length --;

	freeNode(&N);
}

// Prints the values in List L from front to back
// to the file pointed to by out, formatted as a
// space-separated string.
// For those familiar with Java, this is similar
// to toString()in Java.

void printList(FILE* out, List L){

	Node N = NULL;  // This pointer will travel through the list



	if(L == NULL){
		printf("List Error: calling printList() on Null List reference\n");
		exit(1);
	}

	if(L->length == 0){
		printf("List Error: calling printList() on a empty List\n");
		//exit(1);
	}

	for(N = L->front; N != NULL; N = N->next){
		fprintf(out, "%d ", N->data);
		//printf("%d ", N->data);
		//fprintf(out, "%s", "I am in printlist function....\n");
	}

	fprintf(out, "\n");

}

// This is my own helper functionto help me change 
// the data in a speicific node with a parameter data
void changeData(Node N, int data){

	N->data = data;
}

bool doesNodeExist(List L, int data){

	Node current = L->front;

	for(int i = 0; i < L->length; i++){
		if (current->data == data) return true;
		current = current->next;
	}

	return false;

}

int dataValueAtIndex(List L, int index){
	Node current = L->front;

	for(int i = 0; i < index; i++){
		current = getNextNode(current);
	}

	return getValue(current);
}

Node giveMeNodeIfIGiveYouData(List L, int data){
	Node current = L->front;

	for(int i = 0; i < L->length; i++){
		if (current->data == data) return current;
		current = current->next;
	}

	return NULL;
}

void detachNode(List L, Node N) {
    if (N == NULL)
        return;
    Node n = NULL;
    for (n = L->front; n != NULL; n = n->next) {
        if (n == N)
            break;
    }
    if (n == NULL)
        return;
    n = N->next;
    Node p = N->prev;
    if (n != NULL) {
        n->prev = p;
    }
    if (p != NULL) {
        p->next = n;
    }
    if (L->front == N) {
        L->front = n;
    }
    if (L->back == N) {
        L->back = p;
    }
    L->length -= 1;

    free(N);
    N = NULL;
}

List copyList(List L){
	List copyL = newList();

	while(length(L)){
		prepend(copyL, backValue(L));
		deleteBack(L);
	}
	

	return copyL; 
}


