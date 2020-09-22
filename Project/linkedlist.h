#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct _Node {
    int* vertices; /*list of indexes of vertices in sub mat in ascending order*/
    int lenOfVertices; /* length of the array vertices */
    struct _Node* next; /*points to next Node*/
    struct _Node* prev; /*points to previous Node*/

    void   (*free)(struct _Node* node);
} Node;

typedef struct _LinkedList {
    Node* head;
    Node* tail;
    int *len;

    /* Allocates a new Node and inserts it to the end of the list */
    void   (*insertLast)(struct _LinkedList* list, int* new_val, int len0fVal);

    /* Allocates a new Node and inserts it to the beginning of the list */
    void   (*insertFirst)(struct _LinkedList* list, int* new_val, int len0fVal);

    /*Recieves a pointer to a node in the list and delet it */
    void   (*deleteNode)(struct _LinkedList* list, Node* node);

    /*Delte the tail of the list  */
    void (*deleteTail)(struct _LinkedList* list);

    /* frees all resources used by list */
    void   (*free)(struct _LinkedList* list);

} LinkedList;

/*Creates an empty linked list if val == NULL and len = 0.
 * or a linked list with one node s.t node->nodes = val & node->lenOfVertices = len*/
LinkedList* allocate_LinkedList(int* val, int len);

/*Allocares a new Node with vertices = val, lenOfVertices = lenOfVertices, next = next, prev = prev */
Node* allocate_Node(int* val, int lenOfVertices, Node* next, Node* prev);

#endif 