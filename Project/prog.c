#include <stdlib.h>
#include <stdio.h>
#include "spmat.h"
#include "submat.h"
#include "linkedlist.h"
#include "division.h"

void readInputToAdjMatrixFile(char*, char*, int*, int*);
void setToZero(double*, int);
void createExpMat(double*, int*, int, int);
void  divideNetworkIntoModularityGroups(LinkedList*, LinkedList*, spmat*, double*, int);
void writeToOutputFile(char*, LinkedList*);


int main(int argc, char* argv[]) {
	FILE* inputFile;
	int k, i, numOfNodes, nnz = 0, sumOfDegrees = 0, * degree, * nodes;
	spmat* adjMatrix;
	double* expNumOfEdg;
	LinkedList* P, * O;

	if (argc != 3) {
		exit(1);/*replace with error*/
	}

	inputFile = fopen(argv[1], "r");
	if (inputFile == NULL) {
		exit(3);/*replace with error*/
	}

	k = fread(&numOfNodes, sizeof(int), 1, inputFile);
	if (k != 1) {
		exit(4);/*replace with error*/
	}

	fclose(inputFile);

	printf("numOfNodes=%d\n", numOfNodes);

	degree = (int*)malloc(numOfNodes * sizeof(int));
	if (degree == NULL){
		exit(2);/*replace with error*/
	}
	expNumOfEdg = (double*)malloc(numOfNodes * numOfNodes * sizeof(double));
	if (expNumOfEdg == NULL){
		exit(2);/*replace with error*/
	}
	nodes = (int*)malloc(numOfNodes * sizeof(int));
	if (nodes == NULL){
		exit(2);/*replace with error*/
	}

	readInputToAdjMatrixFile(argv[1], "adj_matrix", degree, &nnz);

	adjMatrix = spmat_allocate_array(numOfNodes, nnz);

	/* Calls add_row n times in order to initialize the values of spmat*/
	readMatrixFileToSpmat(adjMatrix, "adj_matrix");

	/*Calculates sum of degrees*/
	for (i = 0; i < numOfNodes; i++) {
		sumOfDegrees += *(degree + i);
	}

	/*Calculates the expected number of edges between i and j for i,j= 0,...,n-1 and insert to mat*/
	createExpMat(expNumOfEdg, degree, numOfNodes, sumOfDegrees);

	for (i = 0; i < numOfNodes; i++) {
		*(nodes + i) = i;
	}

	printf("num of nodes = %d \n", numOfNodes);


	P = allocate_LinkedList(nodes, numOfNodes);
	O = allocate_LinkedList(NULL, 0);

	divideNetworkIntoModularityGroups(P, O, adjMatrix, expNumOfEdg, numOfNodes);


	writeToOutputFile(argv[2], O);

	/*free(nodes);*/
	free(degree);
	free(expNumOfEdg);
	(*adjMatrix->free)(adjMatrix);

	(*P->free)(P);
	(*O->free)(O);

	return 0;
	
}

void readInputToAdjMatrixFile(char* input, char* output, int *degree, int *nnz) {
	int i, j, n, k, currDegree, * neighbors;
	double* row;
	FILE* inputFile, * adjMatrixFile;

	inputFile = fopen(input, "r");
	if (inputFile == NULL){
		exit(3);/*replace with error*/
	}
	adjMatrixFile = fopen(output, "w");
	if (adjMatrixFile == NULL){
		exit(3);/*replace with error*/
	}

	k = fread(&n, sizeof(int), 1, inputFile);
	if (k != 1) {
		exit(4);/*replace with error*/
	}

	for (i = 0; i < 2; i++) {
		k = fwrite(&n, sizeof(int), 1, adjMatrixFile);
		if (k != 1) {
			exit(4);/*replace with error*/
		}
	}

	row = (double*)malloc(n * sizeof(double));
	if (row == NULL){
		exit(2);/*replace with error*/
	}
	neighbors = (int*)malloc(n * sizeof(int));
	if (neighbors == NULL){
		exit(2);/*replace with error*/
	}

	for (i = 0; i < n; i++) {
		setToZero(row, n);
		k = fread(&currDegree, sizeof(int), 1, inputFile);
		if (k != 1) {
			exit(4);/*replace with error*/
		}

		*(degree + i) = currDegree;

		printf("degree of node %d is %d\n", (i), currDegree);
		*nnz += currDegree;
		if (currDegree >= n) {
			exit(6);/*replace with error*/
		}
		k = fread(neighbors, sizeof(int), currDegree, inputFile);
		if (k != currDegree) {
			exit(4);/*replace with error*/
		}
		printf("neighbors are:\n");
		for (j = 0; j < currDegree; j++) {
			printf("%d", *(neighbors + j));
		}
		printf("\n");
		for (j = 0; j < currDegree; j++) {
			row[neighbors[j]] = 1.0;
		}

		printf("row num %d of matrix is:", i);
		for (j = 0; j < n; j++) {
			printf("%f", *(row + j));
		}
		printf("\n");

		k = fwrite(row, sizeof(double), n, adjMatrixFile);
		if (k != n) {
			exit(4);/*replace with error*/
		}
	}
	
	fclose(inputFile);
	fclose(adjMatrixFile);

	free(row);
	free(neighbors);

}

void setToZero(double* row, int len) {
	int i;

	for (i = 0; i < len; i++) {
		row[i] = 0.0;
	}
}

void createExpMat(double* expNumOfEdg, int* degree, int numOfNodes, int sumOfDegrees) {
	int i, j;
	double temp;

	for (i = 0; i < numOfNodes; i++) {
		temp = (double)(*(degree + i)) / (double)(sumOfDegrees);
		for (j = 0; j < numOfNodes; j++) {
			*(expNumOfEdg + i * numOfNodes + j) = (double)(*(degree + j)) * temp;
		}
	}
}

void  divideNetworkIntoModularityGroups(LinkedList *P, LinkedList *O, spmat * adjMatrix, double* expNumOfEdg, int numOfNodes){
	submat* modulMat;
	int i, j, count = 0;
	Node* g;

	while (*(P->len)) {
		int n, s1 = 0, s2 = 0;
		double* division;

		printf("loop num %d\n", count);
		count++;

		g = P->tail;

		n = g->lenOfNodes;

		modulMat = submat_allocate(adjMatrix, expNumOfEdg, g->nodes, n, numOfNodes);

		printf("submat=\n");
		for (i = 0; i < n; i++) {
			printf("row num %d= ", g->nodes[i]);
			for (j = 0; j < n; j++) {
				printf(" %f ", (*modulMat->getVal)(modulMat, g->nodes[i], g->nodes[j]));
			}
			printf("\n");
		}

		division = divideIntoTwo(modulMat);

		for (i = 0; i < n; i++) {
			if (*(division + i) == 1.0) {
				s1++;
			}
			else {
				s2++;
			}
		}

		if (s1 == 0 || s2 == 0) {
			int* nodes;

			nodes = (int*)malloc(n * sizeof(int));
			if (nodes == NULL) {
				exit(2);/*replace with error*/
			}

			for (i = 0; i < n; i++) {
				*(nodes + i) = *(g->nodes + i);
			}
			printf("g is indivisible\n");
			(*O->insertLast)(O, nodes, n);
		}

		else {
			int* g1, * g2, index1 = 0, index2 = 0;
			g1 = (int*)malloc(s1 * sizeof(int));
			if (g1 == NULL) {
				exit(2);/*replace with error*/
			}
			g2 = (int*)malloc(s2 * sizeof(int));
			if (g2 == NULL) {
				exit(2);/*replace with error*/
			}


			for (i = 0; i < n; i++) {
				if (*(division + i) == 1.0) {
					*(g1 + index1) = *((g->nodes) + i);
					index1++;
				}
				else {
					*(g2 + index2) = *((g->nodes) + i);
					index2++;
				}
			}

			if (s1 == 1) {
				(*O->insertLast)(O, g1, s1);
			}
			else {
				(*P->insertLast)(P, g1, s1);
			}

			if (s2 == 1) {
				(*O->insertLast)(O, g2, s2);
			}
			else {
				(*P->insertLast)(P, g2, s2);
			}
		}

		(*P->deleteNode)(P, g);
		free(division);
		(*modulMat->free)(modulMat);
	}
}

void writeToOutputFile(char* filename, LinkedList *O) {
	FILE* outputFile;
	int k, size, i, j;
	Node* currNode;

	outputFile = fopen(filename, "w");
	if (outputFile == NULL) {
		exit(3);
	}

	k = fwrite(O->len, sizeof(int), 1, outputFile);
	if (k != 1) {
		exit(4);/*replace withh error*/
	}

	printf("output:\n");
	printf("num of groups: %d\n", *(O->len));

	currNode = O->head;
	i = 1;

	do {
		printf("group num %d:\n", i);
		i++;

		size = currNode->lenOfNodes;
		printf("size of group=%d " , size);
		k = fwrite(&size, sizeof(int), 1, outputFile);
		if (k != 1) {
			exit(4);/*replace withh error*/
		}

		k = fwrite(currNode->nodes, sizeof(int), size, outputFile);
		if (k != size) {
			exit(4);/*replace withh error*/
		}

		for (j = 0; j < size; j++) {
			printf(" %d ", *(currNode->nodes + j));
		}
		printf("\n");

		currNode = currNode->next;

	} while (currNode != O->head);

	fclose(outputFile);
}


	