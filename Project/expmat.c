#include "util.h"
#include "expmat.h"

void freeExpMat(struct _expmat*);
void add_degreeExpMat(struct _expmat*, double, int);
int getDegreeExpMat(struct _expmat*, int);
double getExpNumOfEdgesExpMat(struct _expmat*, int, int);
void multExpMat(struct _expmat*, int*, int, const double*, double*);

expmat* allocate_expmat(int numOfVertices) {
	expmat *mat;
	int* degreeOfVertex;

	mat = (expmat*)allocate_memory(1, sizeof(expmat));
	degreeOfVertex = (int*)allocate_memory(numOfVertices, sizeof(int));

	mat->degreeOfVertex = degreeOfVertex;
	mat->sumOfDegrees = 0;

	mat->free = &freeExpMat;
	mat->add_degree = &add_degreeExpMat;
	mat->getDegree = &getDegreeExpMat;
	mat->getExpNumOfEdges = &getExpNumOfEdgesExpMat;
	mat->mult = &multExpMat;

	return mat;
}


void freeExpMat(struct _expmat* mat) {
	free(mat->degreeOfVertex);
	free(mat);
}

void add_degreeExpMat(struct _expmat* mat, double degree, int indexOfVertex) {
	int* degrees = mat->degreeOfVertex;

	*(degrees + indexOfVertex) = degree;
	mat->sumOfDegrees += degree;
}

int getDegreeExpMat(struct _expmat* mat, int i) {
	int* degrees = mat->degreeOfVertex;

	return *(degrees + i);
}

double getExpNumOfEdgesExpMat(struct _expmat* mat, int i, int j) {
	int degreeI = mat->degreeOfVertex[i], degreeJ = mat->degreeOfVertex[j];

	return ((double)degreeI * (double)degreeJ) / (double)(mat->sumOfDegrees);
}


void multExpMat(struct _expmat* mat, int* verticesOfSub, int sizeOfSub, const double* vector, double* result) {
	int i, *degreeOfVertex = mat->degreeOfVertex, m = mat->sumOfDegrees;
	double *myVector, sum;

	myVector = (double*)allocate_memory(sizeOfSub, sizeof(double));

	for (i = 0; i < sizeOfSub; i++) {
		*(myVector + i) =(double)*(degreeOfVertex + *(verticesOfSub + i));
	}

	sum = dotProduct(myVector, vector, sizeOfSub);
	
	for (i = 0; i < sizeOfSub; i++) {
		*(result + i) = (sum * *(myVector + i)) / (double)m;
	}

	free(myVector);
}
