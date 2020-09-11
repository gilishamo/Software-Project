#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "submat.h"
#include "powerIteration.h"

void setAllValues(double*,int, double);
void computeDivision(double*, double*, int);

double* divideIntoTwo(submat *modulMat, double * eigenValue) {
	double* eigenVector, *tempVector, temp, * division;
	int n = modulMat->sizeOfSub;

	eigenVector = (double*)allocate_memory(n, sizeof(double));
	eigenValue = (double*)allocate_memory(1, sizeof(double));
	division = (double*)allocate_memory(n, sizeof(double));
	tempVector = (double*)allocate_memory(n, sizeof(double));
	
	setAllValues(division, n, 1.0);

	powerIterationWithMatrixShifting(modulMat, eigenVector, eigenValue);

	if (*eigenValue <= 0) {
		goto end;
	}

	computeDivision(eigenVector, division, n);

	(*(modulMat->mult))(modulMat, division, tempVector);
	temp = dotProduct(division, tempVector, n);

	if (temp <= 0) {
		setAllValues(division, n, 1.0);
		goto end;
	}

	end:
	free(eigenValue);
	free(eigenVector);
	free(tempVector);

	return division;
}

void setAllValues(double* division, int len, double val){
	int i;

	for (i = 0; i < len; i++) {
		*(division + i) = val;
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