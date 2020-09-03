#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "spmat.h"
#include "linkedlist.h"

/*int countNnz(char*);
void readInputMatrix(spmat*, char*);
void setToZero(int*, int);*/

/*
int main(int argc, char* argv[]) {
	FILE* inp;
	int k, * nodes, degree, sumOfNodes;

	if (argc != 2) {
		exit(1);
	}

	inp = fopen(argv[1], "w");
	assert(inp != NULL);

	sumOfNodes = 6;

	k = fwrite(&sumOfNodes, sizeof(int), 1, inp);
	assert(k == 1);


	degree = 1;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 1;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 0;
	*(nodes + 1) = 2;
	*(nodes + 2) = 3;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 1;
	*(nodes + 1) = 3;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 1;
	*(nodes + 1) = 2;
	*(nodes + 2) = 4;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 3;
	*(nodes + 1) = 5;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 1;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 4;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	fclose(inp);

	return 0;
} */
/*
	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 1;
	*(nodes + 1) = 2;
	*(nodes + 2) = 9;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 0;
	*(nodes + 1) = 2;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 0;
	*(nodes + 1) = 1;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 4;
	*(nodes + 1) = 5;
	*(nodes + 2) = 9;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 3;
	*(nodes + 1) = 5;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 3;
	*(nodes + 1) = 4;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 7;
	*(nodes + 1) = 8;
	*(nodes + 2) = 9;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 6;
	*(nodes + 1) = 8;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 2;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 6;
	*(nodes + 1) = 7;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	degree = 3;
	nodes = (int*)malloc(degree * sizeof(int));
	assert(nodes != NULL);
	k = fwrite(&degree, sizeof(int), 1, inp);
	assert(k == 1);
	*(nodes) = 0;
	*(nodes + 1) = 3;
	*(nodes + 2) = 6;
	k = fwrite(nodes, sizeof(int), degree, inp);
	assert(k == degree);
	free(nodes);

	fclose(inp);

	return 0;
}*/

	/*LinkedList *list;
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

	return 0; */

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
	
}*/
/*

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
*/

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

/*
void setToZero(int* row, int len) {
	int i;

	for (i = 0; i < len; i++) {
		row[i] = 0;
	}
}
*/