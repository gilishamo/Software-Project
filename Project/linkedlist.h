#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct _Node {
    int* nodes;
    int lenOfNodes;
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

/*Creates an empty linked list if val == NULL and n = 0.
 * or a linked list with one node s.t node->nodes = val & node->lenOfNodes = n*/
LinkedList* allocate_LinkedList(int* val, int n);

Node* allocate_Node(int* val, int lenOfNodes, Node* next, Node* prev);

#endif 