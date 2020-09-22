#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "util.h"
#include "submat.h"
#include "powerIteration.h"

void computeDivision(double*, double*, int);

double* divideIntoTwo(submat *modulMat, double * eigenValue) {
	double* eigenVector, *tempVector, temp, * division;
	int n = modulMat->sizeOfSub;
	
	eigenVector = (double*)allocate_memory(n, sizeof(double));
	division = (double*)allocate_memory(n, sizeof(double));
	tempVector = (double*)allocate_memory(n, sizeof(double));
	
	setAllValues(division, n, 1.0);

	powerIterationWithMatrixShifting(modulMat, eigenVector, eigenValue);
	
	if (*eigenValue <= EPSILON) {
		goto end;
	}

	computeDivision(eigenVector, division, n);

	(*(modulMat->mult))(modulMat, division, tempVector);
	temp = dotProduct(division, tempVector, n);

	if (temp <= EPSILON) {
		setAllValues(division, n, 1.0);
		goto end;
	}

	end:
	free(eigenVector);
	free(tempVector);

	return division;
}

void computeDivision(double* eigenVector, double* division, int n) {
	int i;

	for (i = 0; i < n; i++) {
		if (*(eigenVector + i) > EPSILON) {
			*(division + i) = 1.0;
		}
		else {
			*(division + i) = -1.0;
		}
	}
}