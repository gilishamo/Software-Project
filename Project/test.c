#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "spmat.h"
#include "linkedlist.h"

int countNnz(char*);
void readInputMatrix(spmat*, char*);


int main(int argc, char* argv[]) {
	LinkedList *list;
	int** vals, *f, *s, *t;
	Node* temp;

	vals = (int**)malloc(3 * sizeof(int*));
	assert(vals != NULL);
	f = (int*)malloc(sizeof(int));
	assert(f != NULL);
	s = (int*)malloc(sizeof(int));
	assert(s != NULL);
	t = (int*)malloc(sizeof(int));
	assert(t != NULL);

	*f = 1;
	*s = 2;
	*t = 3;

	*(vals) = f;
	*(vals + 1) = s;
	*(vals + 2) = t;

	list = allocate_LinkedList(vals, 3);

	temp = list->head;
	printf("list:\n");
	do {
		printf("%d ", *(temp->val));
		temp = temp->next;
	} while (temp != list->head);
	printf("\n");

	temp = (*list->DeleteNode)(list, list->head);

	(*temp->free)(temp);

	temp = list->head;
	printf("list:\n");
	do {
		printf("%d ", *(temp->val));
		temp = temp->next;
	} while (temp != list->head);
	printf("\n");

	(*list->free)(list);

	free(vals);

	return 0;
	
	/*
	FILE* inputFile, * vectorFile;
	double* vector, * result;
	spmat* mat;
	int vLen;
	int i, j, n, nnz, k, nodes[3] = { 0,1,3 };

	inputFile = fopen(argv[1], "r");
	assert(inputFile != NULL);
	for (i = 0; i < 2; i++) {
		k = fread(&n, sizeof(int), 1, inputFile);
		assert(k == 1);
	}

	vectorFile = fopen(argv[2], "r");
	assert(vectorFile != NULL);

	k = fread(&j, sizeof(int), 1, vectorFile);
	assert(k == 1);

	k = fread(&vLen, sizeof(int), 1, vectorFile);
	assert(k == 1);

	vector = (double*)malloc(vLen * sizeof(double));
	assert(vector != NULL);
	result = (double*)malloc(vLen * sizeof(double));
	assert(result != NULL);

	k = fread(vector, sizeof(double), vLen, vectorFile);
	assert(k == vLen);


	printf("vector=\n");
	for (i = 0; i < vLen; i++) {
		printf("%f ", *(vector + i));
	}
	printf("\n");

	nnz = countNnz(argv[1]);
	mat = spmat_allocate_array(n, nnz);

	readInputMatrix(mat, argv[1]);

	(*(mat->mult))(mat, vector, result, nodes, vLen);

	printf("result=\n");
	for (i = 0; i < vLen; i++) {
		printf("%f ", *(result + i));
	}
	printf("\n");

	fclose(vectorFile);
	fclose(inputFile);

	free(vector);
	free(result);

	return 0;
	*/
}

int countNnz(char* filename) {
	double* row;
	int n, i, j, k, count = 0;
	FILE* file;

	file = fopen(filename, "r");
	assert(file != NULL);

	for (i = 0; i < 2; i++) {
		k = fread(&n, sizeof(int), 1, file);
		assert(k == 1);
	}

	row = (double*)malloc(n * sizeof(double));
	assert(row != NULL);

	for (i = 0; i < n; i++) {
		k = fread(row, sizeof(double), n, file);
		assert(k == n);
		for (j = 0; j < n; j++) {
			if (*(row + j) != 0) {
				count++;
			}
		}
	}

	fclose(file);
	free(row);

	return count;
}

void readInputMatrix(spmat* spmat, char* fileName) {
	int i, j, k, n;
	double* row;
	FILE* file;

	file = fopen(fileName, "r");
	assert(file != NULL);

	for (i = 0; i < 2; i++) {
		k = fread(&n, sizeof(int), 1, file);
		assert(k == 1);
	}

	row = (double*)malloc(n * sizeof(double));
	assert(row != NULL);

	for (i = 0; i < n; i++) {
		k = fread(row, sizeof(double), n, file);
		assert(k == n);
		printf("row num %d=\n", i);
		for (j = 0; j < n; j++) {
			printf("%f ", *(row + j));
		}
		printf("\n");
		(*(spmat->add_row))(spmat, row, i);
	}
}


/*
void createInputFile(char *fileName, int numOfNodes) {
	FILE* output;
	int k, i, j, currDegree, currIndex = 0;
	int* neighbors;

	output = fopen(fileName, "w");
	assert(output != NULL);

	srand(time(NULL));

	k = fwrite(&numOfNodes, sizeof(int), 1, output);
	assert(k == 1);

	for (i = 1; i <= numOfNodes; i++) {
		k = fwrite(&i, sizeof(int), 1, output);
		assert(k == 1);

		currDegree = rand() % (numOfNodes);

		neighbors = (int*)malloc(currDegree * sizeof(int));
		assert(neighbors != NULL);

		k = fwrite(&currDegree, sizeof(int), 1, output);
		assert(k == 1);

		for (j = 0; j < currDegree; j++) {
			
	}

		free(neighbors);
	}*/
