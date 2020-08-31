#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct _Node {
    int* val;
    struct _Node* next; /*points to next group*/
    struct _Node* prev;

    void   (*free)(struct _Node* node);
} Node;

typedef struct _LinkedList {
    Node* head;
    Node* tail;
    int *len;

    void   (*insertLast)(struct _LinkedList* list, int* new_val);

    void   (*insertFirst)(struct _LinkedList* list, int* new_val);

    Node*   (*DeleteNode)(struct _LinkedList* list, Node* node);

    void   (*free)(struct _LinkedList* list);

} LinkedList;

LinkedList* allocate_LinkedList(int** val, int n);

Node* allocate_Node(int* val, Node* next, Node* prev);

#endif 