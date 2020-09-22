#ifndef _POWERITERATIOM_H
#define _POWERITERATIOM_H

#include "submat.h"

/*Computes leading eigenpair eigenVector, eigenValue of the modularity matrix modulMatrix using matrix shifting,
* eigenVector, eigenValue are pre allocated*/
void powerIterationWithMatrixShifting(submat* modulMatrix, double* eigenVector, double* eigenValue);\

/*return the dot product of row and len*/
double dotProduct(double* row, double* col, int len);

#endif 