#include <assert.h>
# include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<math.h>
#include "spmat.h"
#include "submat.h"

void createRandomVector(double*, int);
int calcDiff(double*, double*, int);
double dotProduct(double*, double*, int);
double norm1(submat*);

void powerIterationWithMatrixShifting(submat *modulMatrix, double* eigenVector, double* eigenValue) {
	int i, diff = 0, n = modulMatrix->sizeOfSub;
	double magn, norm;
	double* tempVector;
	
	tempVector = (double*)malloc(n * sizeof(double));
	assert(tempVector != NULL); /*replace with error*/

	norm = norm1(modulMatrix);
	
	/*randomize b0*/
	createRandomVector(tempVector, n);

	/*power iteration*/
	while (diff == 0) {
		(*(modulMatrix->mult))(modulMatrix, tempVector, eigenVector);

		for (i = 0; i < n; i++) {
			*(eigenVector + i) += *(tempVector + i) * norm;
		}

		magn = sqrt(dotProduct(eigenVector, eigenVector, n));
		for (i = 0; i < n; i++) {
			*(eigenVector + i) /= magn;
		}

		diff = calcDiff(tempVector, eigenVector, n);

		for (i = 0; i < n; i++) {
			*(tempVector + i) = *(eigenVector + i);
		}
	}
	
	/*Computing the eigenValue*/

	(*(modulMatrix->mult))(modulMatrix, eigenVector, tempVector);

	for (i = 0; i < n; i++) {
		*(tempVector + i) += *(eigenVector + i) * norm;
	}

	*eigenValue = (dotProduct(eigenVector, tempVector, n)) / (dotProduct(eigenValue, eigenValue, n)) - norm;

	free(tempVector);

}

void createRandomVector(double* vector, int n)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		vector[i] = rand();
	}
}


int calcDiff(double* vector, double* newVector, int n)
{
	int i;
	double epsilon = 0.00001;
	for (i = 0; i < n; i++)
	{
		if (fabs(newVector[i] - vector[i]) >= epsilon)
		{
			return 0;
		}
	}
	return 1;
}

double dotProduct(double* row, double *col,  int len)
{
	int i;
	double magn = 0;
	for (i = 0; i < len; i++)
	{
		magn += row[i] * col[i];
	}

	return magn;
}

double norm1(submat *modulMat) {
	double sum, max = 0;
	int i, j, n = modulMat->sizeOfSub, *nodes = modulMat->nodes;

	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j < n; j++) {
			sum += abs((*(modulMat->getVal))(modulMat, nodes[i], nodes[j]));
		}

		if (sum > max) {
			max = sum;
		}
	}

	return max;
}

