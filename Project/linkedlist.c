#include <assert.h>
#include <stdlib.h>
#include "linkedlist.h"

void insertLastLL(struct _LinkedList*, int*);
void insertFirstLL(struct _LinkedList*, int*);
Node* DeleteNodeLL(struct _LinkedList*, Node*);
void freeLinkedList(struct _LinkedList*);
void freeNode(struct _Node* node);

Node* allocate_Node(int* val, Node* next, Node* prev) {
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	assert(newNode != NULL); /*replace with error*/

	newNode->val = val;
	newNode->next = next;
	newNode->prev = prev;

	newNode->free = &freeNode;

	return newNode;
}

void freeNode(struct _Node* node) {
	free(node->val);
	free(node);
}

LinkedList* allocate_LinkedList(int** val, int n) {
	LinkedList* list;
	int i, *listLen;

	list = (LinkedList*)malloc(sizeof(LinkedList));
	assert(list != NULL); /*replace with error*/
	listLen = (int*)malloc(sizeof(int));
	assert(listLen != NULL);
	*listLen = 0;

	list->head = NULL;
	list->tail = NULL;
	list->len = listLen;

	list->DeleteNode = &DeleteNodeLL;
	list->free = &freeLinkedList;
	list->insertFirst = &insertFirstLL;
	list->insertLast = &insertLastLL;

	for (i = 0; i < n; i++) {
		(*list->insertLast)(list, *(val + i));
	}

	return list;
}

void insertLastLL(struct _LinkedList* list, int* new_val) {
	Node* new;
	int* len = list->len;

	if ((*list->len) == 0) {
		new = allocate_Node(new_val, NULL, NULL);
		list->head = new;
		list->tail = new;
		new->next = list->tail;
		new->prev = list->head;
	}

	else {
		new = allocate_Node(new_val, list->head, list->tail);
		list->head->prev = new;
		list->tail->next = new;

		list->tail = new;
	}


	*len +=1;
	
}

void insertFirstLL(struct _LinkedList* list, int* new_val) {
	Node* new;
	int* len = list->len;

	if ((*list->len) == 0) {
		new = allocate_Node(new_val, NULL, NULL);
		list->head = new;
		list->tail = new;
		new->next = list->head;
		new->prev = list->tail;
	}

	else {
		new = allocate_Node(new_val, list->head, list->tail);
		list->head->prev = new;
		list->tail->next = new;

		list->head = new;
	}

	(*len)++;

}

Node* DeleteNodeLL(struct _LinkedList* list, Node* node){
	int* len = list->len;
	if (node == list->head) {
		list->head = node->next;
	}

	if (node == list->tail) {
		list->tail = node->prev;
	}

	(node->prev)->next = node->next;
	(node->next)->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;

	
	(*len)--;

	return node;

	}


void freeLinkedList(struct _LinkedList* list) {
	Node* temp;
	int i, len = *(list->len);

	for (i = 0; i < len; i++) {
		temp = list->head;
		list->head = temp->next;
		free(temp->val);
		free(temp);
	}

	free(list->len);
	free(list);

}