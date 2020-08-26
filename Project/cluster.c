#include <assert.h> /*delete*/
#include <stdlib.h>
#include <stdio.h>
#include "spmat.h"

void readInputToAdjMatrixFile(FILE*, FILE*, int*, int*);
void setToZero(double*, int);

int main(int argc, char* argv[]) {
	FILE* inputFile, *outputFile, *adjMatrixFile;
	int k, i, j, numOfNodes, nnz = 0, sumOfDegrees = 0;
	int* degree;
	spmat* adjMatrix;
	double *expNumOfEdg , temp;


	assert(argc == 3); /*replace with error*/

	inputFile = fopen(argv[1], "r");
	assert(inputFile != NULL); /*replace with error*/
	outputFile = fopen(argv[2], "w");
	assert(outputFile != NULL); /*replace with error*/
	adjMatrixFile = fopen("adj_matrix", "w");
	assert(adjMatrixFile != NULL); /*replace with error*/

	k = fread(&numOfNodes, sizeof(int), 1, inputFile);
	assert(k == 1); /*replace with error*/

	printf("numOfNodes=%d\n", numOfNodes);

	degree = (int*)malloc(numOfNodes * sizeof(int));
	assert(degree != NULL);/*replace with error*/
	expNumOfEdg = (double*)malloc(numOfNodes * numOfNodes * sizeof(double));
	assert(expNumOfEdg != NULL);/*replace with error*/

	rewind(inputFile);

	readInputToAdjMatrixFile(inputFile, adjMatrixFile, degree, &nnz);

	rewind(inputFile);
	fclose(adjMatrixFile);

	adjMatrix = spmat_allocate_array(numOfNodes, nnz);

	/* Calls add_row n times in order to initialize the values of spmat*/
	readMatrixFileToSpmat(adjMatrix, "adj_matrix");

	/*Calculates sum of degrees*/
	for (i = 0; i < numOfNodes; i++) {
		sumOfDegrees += *(degree + i);
	}

	/*Calculates the expected number of edges between i and j for i,j= 0,...,n-1 and insert to mat*/
	for (i = 0; i < numOfNodes; i++) {
		temp = (double)(*(degree + i)) / (double)(sumOfDegrees);
		for (j = 0; j < numOfNodes; j++){
			*(expNumOfEdg + i * numOfNodes + j) = (double)(*(degree + j)) * temp;
		}
	}


	fclose(inputFile);
	fclose(outputFile);

	return 0;
	
}

void readInputToAdjMatrixFile(FILE* input, FILE* output, int *degree, int *nnz) {
	int i, j, n, k, currDegree;
	int *neighbors;
	double* row;

	k = fread(&n, sizeof(int), 1, input);
	assert(k == 1); /*replace with error*/

	for (i = 0; i < 2; i++) {
		k = fwrite(&n, sizeof(int), 1, output);
		assert(k == 1); /*replace with error*/
	}

	row = (double*)malloc(n * sizeof(double));
	assert(row != NULL); /*replace with error*/
	neighbors = (int*)malloc(n * sizeof(int));
	assert(neighbors != NULL); /*replace with error*/


	for (i = 0; i < n; i++) {
		setToZero(row, n);
		k = fread(&currDegree, sizeof(int), 1, input);
		assert(k == 1); /*replace with error*/
		printf("degree of node %d is %d\n", (i), currDegree);
		*nnz += currDegree;
		if (currDegree <= n) {
			k = fread(neighbors, sizeof(int), currDegree, input);
			assert(k == currDegree); /*repace with error*/
		}
		else {
			/*return error*/
			return;
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

		k = fwrite(row, sizeof(double), n, output);
		assert(k == n); /*replace with error*/
	}
	
	free(row);
}

void setToZero(double* row, int len) {
	int i;

	for (i = 0; i < len; i++) {
		row[i] = 0.0;
	}
}

	