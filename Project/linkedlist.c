#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

void insertLastLL(struct _LinkedList*, int*, int);
void insertFirstLL(struct _LinkedList*, int*, int);
void deleteNodeLL(struct _LinkedList*, Node*);
void deleteTailLL(struct _LinkedList*);
void freeLinkedList(struct _LinkedList*);
void freeNode(struct _Node* node);

Node* allocate_Node(int* nodes, int lenOfNodes, Node* next, Node* prev) {
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		exit(2);/*replace withh error*/
	}

	newNode->nodes = nodes;
	newNode->lenOfNodes = lenOfNodes;
	newNode->next = next;
	newNode->prev = prev;

	newNode->free = &freeNode;

	return newNode;
}

void freeNode(struct _Node* node) {
	free(node->nodes);
	free(node);
}

LinkedList* allocate_LinkedList(int* val, int n) {
	LinkedList* list;
	int *listLen;

	list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list == NULL) {
		exit(2);/*replace withh error*/
	}
	listLen = (int*)malloc(sizeof(int));
	if (listLen == NULL) {
		exit(2);/*replace withh error*/
	}
	*listLen = 0;

	list->head = NULL;
	list->tail = NULL;
	list->len = listLen;

	list->deleteNode = &deleteNodeLL;
	list->free = &freeLinkedList;
	list->insertFirst = &insertFirstLL;
	list->insertLast = &insertLastLL;
	list->deleteTail = &deleteTailLL;

	if (val != NULL) {
		(*list->insertLast)(list, val, n);
	}

	return list;
}

void insertLastLL(struct _LinkedList* list, int* new_val, int lenOfVal) {
	Node* new;
	int* len = list->len;

	if ((*list->len) == 0) {
		new = allocate_Node(new_val, lenOfVal, NULL, NULL);
		list->head = new;
		list->tail = new;
		new->next = list->tail;
		new->prev = list->head;
	}

	else {
		new = allocate_Node(new_val, lenOfVal, list->head, list->tail);
		list->head->prev = new;
		list->tail->next = new;

		list->tail = new;
	}


	*len +=1;
	
}

void insertFirstLL(struct _LinkedList* list, int* new_val, int lenOfVal) {
	Node* new;
	int* len = list->len;

	if ((*list->len) == 0) {
		new = allocate_Node(new_val, lenOfVal, NULL, NULL);
		list->head = new;
		list->tail = new;
		new->next = list->head;
		new->prev = list->tail;
	}
	else {
		new = allocate_Node(new_val, lenOfVal, list->head, list->tail);
		list->head->prev = new;
		list->tail->next = new;

		list->head = new;
	}

	(*len)++;

}

void deleteNodeLL(struct _LinkedList* list, Node* node){
	int* len = list->len;

	if (node == list->head) {
		if (*(list->len) == 1) {
			list->head = NULL;
			list->tail = NULL;
			node->prev = NULL;
			node->next = NULL;

			(*len)--;

			(*node->free)(node);
			return;
		}

		list->head = node->next;
	}

	if (node == list->tail) {
		/*if (*(list->len) == 1) { same case as before
			list->head = NULL;
			list->tail = NULL;
			node->prev = NULL;
			node->next = NULL;

			(*len)--;

			(*node->free)(node);
			return;
		}*/

		list->tail = node->prev;
	}

	(node->prev)->next = node->next;
	(node->next)->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;
	
	(*len)--;

	(*node->free)(node);
	return;

}

void deleteTailLL(struct _LinkedList* list) {
	Node* tail = list->tail;
	int* len = list->len;

	if (*(list->len) == 1) {
		list->tail = NULL;
		list->head = NULL;

		tail->next = NULL;
		tail->prev = NULL;

		*(list->len) = 0;

		(*tail->free)(tail);
		return;
	}

	list->tail = tail->prev;

	(tail->prev)->next = tail->next;
	(tail->next)->prev = tail->prev;
	tail->prev = NULL;
	tail->next = NULL;


	*(len) -= 1;

	(*tail->free)(tail);
	return;
}


void freeLinkedList(struct _LinkedList* list) {
	Node* temp;
	int i, len = *(list->len);

	for (i = 0; i < len; i++) {
		temp = list->head;
		list->head = temp->next;
		(*temp->free)(temp);
	}

	free(list->len);
	free(list);

}