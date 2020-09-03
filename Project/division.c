#include <stdlib.h>
#include <stdio.h>
#include "submat.h"
#include "powerIteration.h"

void setToTrivialDivision(double*, int);
void computeDivision(double*, double*, int);

double* divideIntoTwo(submat *modulMat) {
	double* eigenVector, * eigenValue, *tempVector, temp, * division;
	int n = modulMat->sizeOfSub;

	eigenVector = (double*)malloc(n * sizeof(double));
	if (eigenVector == NULL){
		exit(2);/*replace with error*/
	}
	eigenValue = (double*)malloc(sizeof(double));
	if (eigenValue == NULL){
		exit(2);/*replace with error*/
	}
	division = (double*)malloc(n * sizeof(double));
	if (division == NULL){
		exit(2);/*replace with error*/
	}
	tempVector = (double*)malloc(n * sizeof(double));
	if (tempVector == NULL){
		exit(2);/*replace with error*/
	}

	setToTrivialDivision(division, n);

	powerIterationWithMatrixShifting(modulMat, eigenVector, eigenValue);

	printf(" eigenValue = %f \n ", *eigenValue);

	if (*eigenValue <= 0) {
		free(eigenValue);
		free(eigenVector);
		free(tempVector);
		return division;
	}

	computeDivision(eigenVector, division, n);

	(*(modulMat->mult))(modulMat, division, tempVector);
	temp = dotProduct(division, tempVector, n);

	if (temp <= 0) {
		setToTrivialDivision(division, n);

		free(eigenValue);
		free(eigenVector);
		free(tempVector);

		return division;
	}

	free(eigenValue);
	free(eigenVector);
	free(tempVector);

	return division;
}

void setToTrivialDivision(double* division, int n) {
	int i;

	for (i = 0; i < n; i++) {
		*(division + i) = 1.0;
	}
}

void computeDivision(double* eigenVector, double* division, int n) {
	int i;

	for (i = 0; i < n; i++) {
		if (*(eigenVector + i) > 0) {
			*(division + i) = 1.0;
		}
		else {
			*(division + i) = -1.0;
		}
	}
}