#include <stdlib.h>
#include <stdio.h>
#include "submat.h"
#include "spmat.h"
#include "expmat.h"
#include "util.h"

double* calculateF(spmat*, expmat*, int*, int);
double getValSubmat(struct _submat*, int, int);
void freeSubmat(struct _submat*);
void multSubMat(struct _submat*, const double*, double*);

submat* submat_allocate(spmat* adjMat, expmat* expMat, int* vertices, int n, int numOfVertices) {
	submat* mat;

	mat = (submat*)allocate_memory(1, sizeof(submat));
		
	mat->free = &freeSubmat;
	mat->mult = &multSubMat;
	mat->getVal = &getValSubmat;

	mat->adjMat = adjMat;
	mat->expMat = expMat;
	mat->vertices = vertices;
	mat->sizeOfSub = n;
	mat->numOfVertices = numOfVertices;
	mat->f = calculateF(adjMat, expMat, vertices, n);

	return mat;
}

double getValSubmat(struct _submat* mat, int i, int j) {
	int *vertices=mat->vertices;
	double *f = mat->f, result = 0;
	spmat* adjMat;
	expmat* expMat;

	expMat = mat->expMat;
	adjMat = mat->adjMat;

	result += (*adjMat->getVal)(adjMat, vertices[i], vertices[j]);

	result -= (*expMat->getExpNumOfEdges)(expMat, vertices[i], vertices[j]);

	if (i == j) {
		result -= *(f + i);
	}

	return result;
}

void freeSubmat(struct _submat* mat) {
	double* f = mat->f;

	free(f);
	free(mat);
}

void multSubMat(struct _submat* mat, const double* vector, double* result) {
	int i, n = mat->sizeOfSub, * vertices = mat->vertices;
	double *f = mat->f, *temp;
	spmat* adjMat;
	expmat* expMat;

	expMat = mat->expMat;
	adjMat = mat->adjMat;

	temp = (double*)allocate_memory(n, sizeof(double));

	/*Calculating adjMat * vector and storing the product in result*/
	(*(adjMat->mult))(adjMat, vector, result, vertices, n); 
	
	/* Calculating expMat * vector and storing the product in temp */
	(*expMat->mult)(expMat, vertices, n, vector, temp);

	for (i = 0; i < n; i++) {
		*(result + i) -= *(temp + i);
		*(result + i) -= *(f + i) * *(vector + i);
	}
}

double* calculateF(spmat *adjMat, expmat *expMat, int* vertices, int sizeOfSub) {
	int i, j;
	double *f;

	f = (double*)allocate_memory(sizeOfSub, sizeof(double));

	for (i = 0; i < sizeOfSub; i++) {
		*(f + i) = 0;
		for (j = 0; j < sizeOfSub; j++) {
			*(f + i) -= (*expMat->getExpNumOfEdges)(expMat, vertices[i], vertices[j]);
			*(f + i) +=(*(adjMat->getVal))(adjMat, vertices[i], vertices[j]);
		}
	}
	return f;
}
