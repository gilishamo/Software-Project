#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<math.h>
#include "spmat.h"
#include "submat.h"
#include "util.h"

void createRandomVector(double*, int);
int calcDiff(double*, double*, int);
double dotProduct(double*, double*, int);
double norm1(submat*);

void powerIterationWithMatrixShifting(submat *modulMatrix, double* eigenVector, double* eigenValue) {
	int i, count = 0, diff = 0, n = modulMatrix->sizeOfSub, maxIteration = modulMatrix->numOfVertices * modulMatrix->numOfVertices;
	double magn, norm;
	double* tempVector;

	
	tempVector = (double*)allocate_memory(n, sizeof(double));

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
		if (magn == EPSILON || magn == 0) {
			traceAndExit(7, "division in zero");
		}
		for (i = 0; i < n; i++) {
			*(eigenVector + i) /= magn;
		}

		diff = calcDiff(tempVector, eigenVector, n);

		for (i = 0; i < n; i++) {
			*(tempVector + i) = *(eigenVector + i);
		}
		count++;
		if (count > maxIteration) {
			traceAndExit(8, "infinite loop");
		}
	}
	
	/*Computing the eigenValue*/

	(*(modulMatrix->mult))(modulMatrix, eigenVector, tempVector);

	for (i = 0; i < n; i++) {
		*(tempVector + i) += *(eigenVector + i) * norm;
	}

	*eigenValue = ((dotProduct(eigenVector, tempVector, n)) / (dotProduct(eigenVector, eigenVector, n))) - norm;

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
	for (i = 0; i < n; i++)
	{
		if (fabs(newVector[i] - vector[i]) >= EPSILON)
		{
			return 0;
		}

		if (newVector[i] == -vector[i]) {
			traceAndExit(8, "infinite loop");
		}
	}
	return 1;
}

double dotProduct(double* row, double *col,  int len)
{
	int i;
	double product = 0;
	for (i = 0; i < len; i++)
	{
		product += row[i] * col[i];
	}

	return product;
}

double norm1(submat *modulMat) {
	double sum, max = 0;
	int i, j, n = modulMat->sizeOfSub;

	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j < n; j++) {
			sum += fabs((*(modulMat->getVal))(modulMat, j, i));
		}
		if (sum > max) {
			max = sum;
		}
	}

	return max;
}

