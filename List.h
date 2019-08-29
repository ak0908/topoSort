// Yasin Aikebaier
// yaikebai
// PA 4
// 
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE



// Exported type --------------------------------------------------------------
// change the pointer data type(ListObj*) to List
// change the pointer data type(NodeObj*) to Node
typedef struct NodeObj* Node;
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node Object. initializes the next and prev pointers and data
Node newNode(int data);

// freeNode()
// frees heap memory pointed to by pN
// sets *pN to NULL
void freeNode(Node* pN);

List newList(void); 			// returns a List which points to a new empty list object

void freeList(List* pL); 		// frees all heap memory associated with its List* argument,
								// and sets *pL to NULL

// Access functions -----------------------------------------------------------
int length(List L); 			// Returns the number of nodes in this List.

int frontValue(List L);			// Returns the integer in the front Node.
								// Precondition: L has at least one Node on it.

int backValue(List L); 			// Returns the integer in the back Node.
								// Precondition: L has at least one Node on it.
int getValue(Node N); 			// Returns the integer in Node N.
								// Precondition: N is not NULL

int equals(List A, List B); 	// Returns 1 if if List A and List B are the same integer
								// sequence, otherwise returns 0.

// Manipulation procedures ----------------------------------------------------

void clear(List L); 			// Resets this List to the empty state.

Node getFront(List L); 			// If List is non-empty, returns the front Node, without
								// changing the List. Otherwise, does nothing.

Node getBack(List L); 			// If List is non-empty, returns the back Node, without
								// changing the List. Otherwise, does nothing.

Node getPrevNode(Node N); 		// Without changing the List that N is on, returns the
								// Node that is previous to Node N on its List. If
								// there is no previous Node, returns NULL.
Node getNextNode(Node N); 		// Without changing the List that N is on, returns the
								// Node that is next after Node N on its List. If
								// there is no next Node, returns NULL.

void prepend(List L, int data); // Inserts a new Node into List L before the front
								// Node that has data as its value. If List is empty,
								// makes that new Node the only Node on the list.

void append(List L, int data); 	// Inserts a new Node into List L after the back
								// Node that has data as its value. If List is empty,
								// makes that new Node the only Node on the list.

void insertBefore(List L, Node N, int data);// Insert a new Node into Node N’s list
								// before Node N that has data as its value.
								// Assume that Node N is on List L. If Node N is
								// the front of List L, then N becomes the new front.
								// Precondition: Node N is not NULL

void insertAfter(List L, Node N, int data); // Insert a new Node into Node N’s list
								// after Node N that has data as its value.
								// Assume that Node N is on List L. If Node N is
								// the back of List L, then N becomes the new back.
								// Precondition: Node N is not NULL

void deleteFront(List L); 		// Deletes the front Node in List L.
								// Precondition: L has at least one Node on it.

void deleteBack(List L); 		// Deletes the back Node in List L.
								// Precondition: L has at least one Node on it.

/*void detachNode(List L, Node N);// Removes N from List L by making the Node before
								// Node N link to the Node that’s after Node N as its
								// next Node, and making the Node after Node N link to
								// the Node that’s before Node N as its previous Node.
//
// After detachNode, Node N should have NULL as both its
// next and previous Nodes.
//
// Special cases:
//
// If Node N is the front the List L, then the Node after
// Node N becomes the front of List L, which should have
// a NULL previous Node.
//
// If Node N is the back of List L, then the Node before
// Node N becomes the back of List L, which should have
// a NULL next Node.
//
// Precondition: N is a Node that’s on List L.
// Other operations -----------------------------------------------------------
*/

void printList(FILE* out, List L); // Prints the values in List L from front to back
								   // to the file pointed to by out, formatted as a
								   // space-separated string.
									// For those familiar with Java, this is similar
									// to toString()in Java.



void changeData(Node N, int data);  // This is my own helper functionto help me change 
									// the data in a speicific node with a parameter data

bool doesNodeExist(List L, int data); // this is my own helper function it returns true if
									  // the data is in the one of the nodes in the list
								
int dataValueAtIndex(List L, int index); // this is my own helper funciton it returns the 
										// data value at the index

Node giveMeNodeIfIGiveYouData(List L, int data);

void detachNode(List L, Node N);

List copyList(List L);

#endif // LSIT_H_INCLUDE