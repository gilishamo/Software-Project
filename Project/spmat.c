#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "spmat.h"
#include "util.h"

void add_arr(struct _spmat*, const double*, int);
void free_arr(struct _spmat*);
void mult_arr(const struct _spmat*, const double*, double*, int*, int);
double getValArray(struct _spmat*, int, int);

spmat* spmat_allocate_array(int n, int nnz) {
	spmat* spmatArray;
	double* val;
	int* col, * row, * index;
	void** arrays;

	arrays = allocate_memory(4, sizeof(void*));
	val = (double*)allocate_memory(nnz, sizeof(double));
	col = (int*)allocate_memory(nnz, sizeof(int));
	row = (int*)allocate_memory(n+1, sizeof(int));
	index = (int*)allocate_memory(1, sizeof(int));

	*(index) = 0;

	*arrays = val;
	*(arrays + 1) = col;
	*(arrays + 2) = row;
	*(arrays + 3) = index;

	spmatArray = (spmat*)allocate_memory(1, sizeof(spmat));

	spmatArray->add_row = &add_arr;
	spmatArray->free = &free_arr;
	spmatArray->mult = &mult_arr;
	spmatArray->getVal = &getValArray;
	spmatArray -> private = arrays;

	(*spmatArray).n = n;
	*(row + n) = nnz;

	return spmatArray;

}

void add_arr(struct _spmat* A, const double* row, int i) {
	int j, n = A->n;
	void** arrays = (A-> private);
	double* val = (double*)*(arrays);
	int* col = (int*)*(arrays + 1);
	int* rowArray = (int*)*(arrays + 2);
	int currIndex = (*(int*)(*(arrays + 3)));

	*(rowArray + i) = currIndex;
	for (j = 0; j < n; j++) {
		if (*(row + j) != 0) {
			*(val + currIndex) = *(row + j);
			*(col + currIndex) = j;
			currIndex = currIndex + 1;
		}
	}
	*((int*)*(arrays + 3)) = currIndex;
}

void free_arr(struct _spmat* A) {
	void** arrays = (A-> private);
	double* val = (double*)*(arrays);
	int* col = (int*)*(arrays + 1);
	int* rowArray = (int*)*(arrays + 2);
	int* index = (int*)*(arrays + 3);

	free(val);
	free(col);
	free(rowArray);
	free(index);
	free(arrays);
	free(A);

	return;
}

void mult_arr(const struct _spmat* A, const double* v, double* result, int* nodes, int len) {
	int i, j, k;
	double sum;
	void** arrays = (A-> private);
	double* val = (double*)*(arrays);
	int* col = (int*)*(arrays + 1);
	int* rowArray = (int*)*(arrays + 2);

	for (j = 0; j < len; j++) {
		sum = 0;
		k = 0;
		for (i = *(rowArray + nodes[j]); i < *(rowArray + nodes[j] + 1); i++) {
			if (k >= len) {
				break;
			}
			while (k < len && *(col + i) > nodes[k]) {
				k += 1;
			}
			if (*(nodes + k) == *(col + i))
			{
				sum = sum + (*(val + i)) * (*(v + k));
				k += 1;
			}
		}
		*(result + j) = sum; 
	}
}


void readMatrixFileToSpmat(spmat* spmat, char* fileName) {
	int i, k, n;
	double* row;
	FILE* file;

	file = fopen(fileName, "r");
	if (file == NULL) {
		traceAndExit(3, "failed to open file");
	}

	for (i = 0; i < 2; i++) {
		k = fread(&n, sizeof(int), 1, file);
		if (k != 1) {
			traceAndExit(4, "failed to read file");
		}
	}

	row = (double*)allocate_memory(n, sizeof(double));

	for (i = 0; i < n; i++) {
		k = fread(row, sizeof(double), n, file);
		if (k != n) {
			traceAndExit(4, "failed to read file");
		}
		(*(spmat->add_row))(spmat, row, i);
	}

	fclose(file);

	free(row);
}

double getValArray(struct _spmat* mat, int i, int j) {
	int n = mat->n, index;
	void** arrays = (mat-> private);
	double* val = (double*)*(arrays);
	int* col = (int*)*(arrays + 1);
	int* rowArray = (int*)*(arrays + 2);

	if(i >= n || j >= n) {
		traceAndExit(5, "invalid access to memory ");
	}

	for (index = *(rowArray + i); index < *(rowArray + i + 1); index++) {
		if (*(col + index) == j) {
			return *(val + index);
		}

		if (*(col + index) > j) {
			return 0.0;
		}
	}

	return 0.0;
}

