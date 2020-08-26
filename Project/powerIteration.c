#include <assert.h>
# include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<math.h>
#include "spmat.h"

void createRandomVector(double*, int);
int calcDiff(double*, double*, int);
double dotProdunt(double*, double*, int);

void powerIterationWithMatrixShifting(spmat *adjMat, double *expMatrix, int n, double* eigenVector, double* eigenValue, double norm) {
	int i, j, k, diff = 0;
	double magn;
	double* tempVector;

	
	tempVector = (double*)malloc(n * sizeof(double));
	assert(tempVector != NULL); /*replace with error*/
	
	/*randomize b0*/
	createRandomVector(tempVector, n);

	/*power iteration*/
	while (diff == 0) {
		(*(adjMat->mult))(adjMat, tempVector, eigenVector);

		for (i = 0; i < n; i++) {
			*(eigenVector + i) += dotProduct(expMatrix + i * n, tempVector, n) + norm * (*(tempVector + i));
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

	(*(adjMat->mult))(adjMat, eigenVector, tempVector);

	for (i = 0; i < n; i++) {
		*(tempVector + i) += dotProduct(expMatrix + i * n, eigenVector, n);
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

double norm1(char* fileName, double* expMat) {
	FILE* adjMat;
	double sum, max = 0, *row;
	int i, j, k, n;

	adjMat = fopen(fileName, "r");
	assert(adjMat != NULL);

	for (i = 0; i < 2; i++) {
		k = fread(&n, sizeof(int), 1, adjMat);
		assert(k == 1);
	}

	row = (double*)malloc(n * sizeof(double));
	assert(row != NULL);

	for (i = 0; i < n; i++) {
		sum = 0;
		k = fread(row, sizeof(double), n, adjMat);
		assert(k == n);

		for (j = 0; j < n; j++) {
			sum += abs(*(row + j) + *(expMat + i * n + j));
		}

		if (sum > max) {
			max = sum;
		}
	}

	return max;
}

