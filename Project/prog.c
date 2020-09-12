#include <stdlib.h>
#include <stdio.h>
#include "spmat.h"
#include "submat.h"
#include "linkedlist.h"
#include "division.h"
#include "util.h"
#include <time.h>
#include "modmax.h"
#include "expmat.h"

void readInputToAdjMatrixFile(char*, char*, expmat*, int*);
void  divideNetworkIntoModularityGroups(LinkedList*, LinkedList*, spmat*, expmat*, int);
void writeToOutputFile(char*, LinkedList*);


int main(int argc, char* argv[]) {
	FILE* inputFile;
	int k, i, numOfVertices, nnz = 0, * vertices;
	spmat* adjMatrix;
	expmat* expNumOfEdgMat;
	LinkedList* P, * O;
	time_t start, end;
	double time;

	start = clock();

	if (argc != 3) {
		if (argc < 3) {
			traceAndExit(1, "too few arguments passed to main");
		}
		else {
			traceAndExit(1, "too many arguments passed to main");
		}
	}

	inputFile = fopen(argv[1], "r");
	if (inputFile == NULL) {
		traceAndExit(3, "failed to open file");
	}

	k = fread(&numOfVertices, sizeof(int), 1, inputFile);
	if (k != 1) {
		traceAndExit(4, "failed to read from file");
	}

	fclose(inputFile);

	expNumOfEdgMat = (expmat*)allocate_expmat(numOfVertices);
	vertices = (int*)allocate_memory(numOfVertices, sizeof(int));
	
	/*Read input file to AdjMatrixFile and calss (*expNumOfEdgMat->add_degree) numOfVertices times in a row */
	readInputToAdjMatrixFile(argv[1], "adj_matrix", expNumOfEdgMat, &nnz);

	adjMatrix = spmat_allocate_array(numOfVertices, nnz);

	/* Calls add_row n times in order to initialize the values of spmat*/
	readMatrixFileToSpmat(adjMatrix, "adj_matrix");

	/*Initializing first group for division aka {0,1,...,numOfVertices-1} */
	for (i = 0; i < numOfVertices; i++) {
		*(vertices + i) = i;
	}

	P = allocate_LinkedList(vertices, numOfVertices);
	O = allocate_LinkedList(NULL, 0);

	divideNetworkIntoModularityGroups(P, O, adjMatrix, expNumOfEdgMat, numOfVertices);

	writeToOutputFile(argv[2], O);


	(*expNumOfEdgMat->free)(expNumOfEdgMat);
	(*adjMatrix->free)(adjMatrix);

	(*P->free)(P);
	(*O->free)(O);

	end = clock();

	time = (double)(end - start) / (CLOCKS_PER_SEC);

	printf("my program took %f sec\n" ,time);

	return 0;
	
}

void readInputToAdjMatrixFile(char* input, char* output, expmat* expNumOfEdgMat, int *nnz) {
	int i, j, n, k, currDegree, * neighbors;
	double* row;
	FILE* inputFile, * adjMatrixFile;

	inputFile = fopen(input, "r");
	if (inputFile == NULL){
		traceAndExit(3, "failed to open file");
	}
	adjMatrixFile = fopen(output, "w");
	if (adjMatrixFile == NULL){
		traceAndExit(3, "failed to open file");
	}

	k = fread(&n, sizeof(int), 1, inputFile);
	if (k != 1) {
		traceAndExit(4, "failed to read file");
	}

	for (i = 0; i < 2; i++) {
		k = fwrite(&n, sizeof(int), 1, adjMatrixFile);
		if (k != 1) {
			traceAndExit(4, "failed to write to file");
		}
	}

	row = (double*)allocate_memory(n, sizeof(double));
	neighbors = (int*)allocate_memory(n, sizeof(int));
	

	for (i = 0; i < n; i++) {
		setAllValues(row, n, 0.0);
		k = fread(&currDegree, sizeof(int), 1, inputFile);
		if (k != 1) {
			traceAndExit(4, "failed to read file");
		}

		(*expNumOfEdgMat->add_degree)(expNumOfEdgMat, currDegree, i);

		*nnz += currDegree;
		if (currDegree >= n) {
			traceAndExit(6, "invalid input");
		}
		k = fread(neighbors, sizeof(int), currDegree, inputFile);
		if (k != currDegree) {
			traceAndExit(4, "failed to read file");
		}
		
		for (j = 0; j < currDegree; j++) {
			row[neighbors[j]] = 1.0;
		}

		k = fwrite(row, sizeof(double), n, adjMatrixFile);
		if (k != n) {
			traceAndExit(4, "failed to write to file");
		}
	}
	
	fclose(inputFile);
	fclose(adjMatrixFile);

	free(row);
	free(neighbors);

}

void  divideNetworkIntoModularityGroups(LinkedList *P, LinkedList *O, spmat * adjMatrix, expmat* expNumOfEdgMat, int numOfVertices){
	int i, n, s1, s2;
	double* division, * eigenVale;
	submat* modulMat;
	Node* g;

	while (*(P->len)) {
		s1 = 0, s2 = 0;

		g = P->tail;

		n = g->lenOfVertices;

		modulMat = submat_allocate(adjMatrix, expNumOfEdgMat, g->vertices, n, numOfVertices);

		eigenVale = (double*)allocate_memory(1, sizeof(double));

		division = divideIntoTwo(modulMat, eigenVale);

		if (*eigenVale != EPSILON || *eigenVale != 0) {
			modularityMaximization(division, n, modulMat);
		}

		for (i = 0; i < n; i++) {
			if (*(division + i) == 1.0) {
				s1++;
			}
			else {
				s2++;
			}
		}

		if (s1 == 0 || s2 == 0) {
			int* vertices;

			vertices = (int*)allocate_memory(n, sizeof(int));

			for (i = 0; i < n; i++) {
				*(vertices + i) = *(g->vertices + i);
			}
			(*O->insertLast)(O, vertices, n);
		}

		else {
			int* g1, * g2, index1 = 0, index2 = 0;
			g1 = (int*)allocate_memory(s1, sizeof(int));
			g2 = (int*)allocate_memory(s2, sizeof(int));

			for (i = 0; i < n; i++) {
				if (*(division + i) == 1.0) {
					*(g1 + index1) = *((g->vertices) + i);
					index1++;
				}
				else {
					*(g2 + index2) = *((g->vertices) + i);
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
	int k, size, i = 1;
	Node* currNode;

	outputFile = fopen(filename, "w");
	if (outputFile == NULL) {
		traceAndExit(3, "failed to open file");
	}

	k = fwrite(O->len, sizeof(int), 1, outputFile);
	if (k != 1) {
		traceAndExit(4, "failed to write to file");
	}

	printf("num of clusters= %d\n", *O->len);

	currNode = O->head;
	do {
		size = currNode->lenOfVertices;
		k = fwrite(&size, sizeof(int), 1, outputFile);
		if (k != 1) {
			traceAndExit(4, "failed to write to file");
		}

		printf("size of group %d is %d ", i, size);
		i++;

		k = fwrite(currNode->vertices, sizeof(int), size, outputFile);
		if (k != size) {
			traceAndExit(4, "failed to write to file");
		}
		printf("vertices are: ");
		for (k = 0; k < size; k++) {
			printf("%d ", currNode->vertices[k]);
		}
		printf("\n");
		currNode = currNode->next;

	} while (currNode != O->head);

	fclose(outputFile);
}


	