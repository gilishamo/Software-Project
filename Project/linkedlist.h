#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct _Node {
    int* vertices; /*list of indexes of vertices in sub mat in ascending order*/
    int lenOfVertices;
    struct _Node* next; /*points to next group*/
    struct _Node* prev;

    void   (*free)(struct _Node* node);
} Node;

typedef struct _LinkedList {
    Node* head;
    Node* tail;
    int *len;

    void   (*insertLast)(struct _LinkedList* list, int* new_val, int len0fVal);

    void   (*insertFirst)(struct _LinkedList* list, int* new_val, int len0fVal);

    void   (*deleteNode)(struct _LinkedList* list, Node* node);

    void (*deleteTail)(struct _LinkedList* list);

    void   (*free)(struct _LinkedList* list);

} LinkedList;

/*Creates an empty linked list if val == NULL and len = 0.
 * or a linked list with one node s.t node->nodes = val & node->lenOfVertices = len*/
LinkedList* allocate_LinkedList(int* val, int len);

Node* allocate_Node(int* val, int lenOfVertices, Node* next, Node* prev);

#endif 