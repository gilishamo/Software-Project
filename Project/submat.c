#include <stdlib.h>
#include <assert.h>
#include "submat.h"
#include "spmat.h"

double* calculateF(submat*);
double getValSubmat(struct _submat*, int, int);
void freeSubmat(struct _submat*);
void multSubMat(submat*, const double*, double*);

submat* submat_allocate(spmat* adjMat, double* expMat, int* nodes, int n, int numOfNodes) {
	submat* mat;

	mat = (submat*)malloc(sizeof(submat));
	assert(mat != NULL); /*replace with error*/

	mat->free = &freeSubmat;
	mat->mult = &multSubMat;
	mat->getVal = &getValSubmat;

	mat->adjMat = adjMat;
	mat->expMat = expMat;
	mat->nodes = nodes;
	mat->sizeOfSub = n;
	mat->numOfNodes = numOfNodes;
	mat->f = calculateF(mat);

	return mat;
}

double getValSubmat(struct _submat* mat, int i, int j) {
	int numOfNodes = mat->numOfNodes;
	double *expMat, *f = mat->f, result = 0;
	spmat* adjMat;

	expMat = mat->expMat;
	adjMat = mat->adjMat;

	result += (*(adjMat->getVal))(adjMat, i, j);

	result += *(expMat + i * numOfNodes + j);

	if (i == j) {
		result -= *(f + i);
	}

	return result;
}

void freeSubmat(struct _submat* mat) {
	double* f = mat->f;

	/*(*mat->adjMat->free)(mat->adjMat);
	free((*mat->nodes));
	free(mat->expMat);*/
	free(f);
	free(mat);
}

void multSubMat(submat* mat, const double* vector, double* result) {
	int i, j, n = mat->sizeOfSub;
	int* nodes = mat->nodes, numOfNodes = mat->numOfNodes;
	double sum;
	double* expMat, *f = mat->f;
	spmat* adjMat;

	expMat = mat->expMat;
	adjMat = mat->adjMat;

	/*Calculating adjMat * vector and storing the product in result*/
	(*(adjMat->mult))(adjMat, vector, result, nodes, n); 
	
	/*Calculating expMat * vector and adding the product to result*/
	for (i = 0; i < n; i++) {
		sum = 0;

		for (j = 0; j < n; j++) {
			sum += *(expMat + nodes[i] * numOfNodes + nodes[j]) * *(vector + j);
			if (i == j) {
				sum -= *(f + i) * *(vector + j); 
			}
		}

		*(result + i) += sum;
	}


}

double* calculateF(submat *B) {
	int n = B->sizeOfSub, numOfNodes = B->numOfNodes, *nodes = B->nodes;
	int i, j;
	double *expMat = B->expMat, *f;
	spmat* adjMat = B->adjMat; 

	f = (double*)malloc(n * sizeof(double));
	assert(f != NULL); /*replace with error*/

	for (i = 0; i < n; i++) {
		*(f + i) = 0;
		for (j = 0; j < n; j++) {
			*(f + i) += *(expMat + *(nodes + i) * numOfNodes + *(nodes + j));
			*(f + i) +=(*(adjMat->getVal))(adjMat, nodes[i], nodes[j]);
		}
	}


	return f;
}
