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
int vecorsAreMinusOfEachOther(double*, double*, double*, int);
double* SingletonNorm1(submat*);

void powerIterationWithMatrixShifting(submat *modulMatrix, double* eigenVector, double* eigenValue) {
	int i, count = 0, diff = 0, n = modulMatrix->sizeOfSub, maxIteration = modulMatrix->numOfVertices * modulMatrix->numOfVertices + 1000* modulMatrix->numOfVertices;
	double magn, * tempVector, * norm, product;
	double *prev;
	
	tempVector = (double*)allocate_memory(n, sizeof(double));
	prev = (double*)allocate_memory(n, sizeof(double));

	norm = SingletonNorm1(modulMatrix);

	/*randomize b0*/
	createRandomVector(tempVector, n);

	/*power iteration*/
	while (diff == 0) {
		(*(modulMatrix->mult))(modulMatrix, tempVector, eigenVector);

		for (i = 0; i < n; i++) {
			*(eigenVector + i) += *(tempVector + i) * *norm;
		}

		
		magn = sqrt(dotProduct(eigenVector, eigenVector, n));
		if (magn > -EPSILON && magn < EPSILON) {
			traceAndExit(7, "division in zero");
		}
		for (i = 0; i < n; i++) {
			*(eigenVector + i) /= magn;
		}

		if (i > modulMatrix->numOfVertices) {
			if (i > modulMatrix->numOfVertices + 1) {
				if (vecorsAreMinusOfEachOther(prev, tempVector, eigenVector, n)) {
					traceAndExit(8, "infinite loop vectors");
				}
			}

			for (i = 0; i < n; i++) {
				*(prev + i) = *(tempVector + i);
			}
		}
		
		diff = calcDiff(tempVector, eigenVector, n);

		for (i = 0; i < n; i++) {
			*(tempVector + i) = *(eigenVector + i);
		}
		count++;
		if (count > maxIteration) {
			traceAndExit(8, "infinite loop num of iteration");
		}
	}
	
	/*Computing the eigenValue*/

	(*(modulMatrix->mult))(modulMatrix, eigenVector, tempVector);

	for (i = 0; i < n; i++) {
		*(tempVector + i) += *(eigenVector + i) * *norm;
	}

	product = dotProduct(eigenVector, eigenVector, n);

	if (-EPSILON < product && product < EPSILON) {
		traceAndExit(7, "division in zero");
	}

	*eigenValue = ((dotProduct(eigenVector, tempVector, n)) / product ) - *norm;

	free(tempVector);
	/*free(prev);*/
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
	}
	return 1;
}

int vecorsAreMinusOfEachOther(double* prev, double* vector, double* newVector, int n) {
	int i;

	for (i = 0; i < n; i++)
	{
		if (newVector[i] != -vector[i]) {
			return 0;
		}
		if (prev[i] != newVector[i]) {
			return 0;
		}
	}

	return 1;

}

double* SingletonNorm1(submat *modulMat) {
	static double norm;
	double sum;
	int i, j, n = modulMat->sizeOfSub;

	if (norm == 0) {
		for (i = 0; i < n; i++) {
			sum = 0;
			for (j = 0; j < n; j++) {
				sum += fabs((*(modulMat->getVal))(modulMat, i, j));/* Modulariy matrix is symmetric hence we can loop over row instead of columns */

			}
			if (sum > norm) {
				norm = sum;
			}
		}
	}

	return &norm;
}

