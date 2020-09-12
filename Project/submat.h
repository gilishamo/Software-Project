#ifndef _SUBMAT_H
#define _SUBMAT_H

#include "spmat.h"
#include "expmat.h"


/*Struct that holds the values of modularity matrix B[g] bar */

typedef struct _submat {
	/*sub graph containes vertices with index nodes[0], nodes[1],.. coresponding to the original mat*/
	int* vertices;

	/*num of nodes in sub graph*/
	int sizeOfSub;

	/*num of nodes in the original graph*/
	int numOfVertices;

	/*pointers to the original matrix B = adjMat + expMat*/
	spmat* adjMat;
	expmat* expMat;

	/* f[i] == sum of row i in modularity matrix B[g]*/
	double* f;

	/* Returns the  value in row i and j of the current sub matrix, meaning nodes[i], nodes[j] are the indices in the original matrix*/
	double	(*getVal)(struct _submat* mat, int i, int j);

	/* Frees all resources used by mat, excluding resources that were pre allocated */
	void	(*free)(struct _submat* mat);

	/* Multiplies matrix mat by vector vector, into result (result is pre-allocated) */
	void	(*mult)(struct _submat* mat, const double* vector, double* result);

}submat;

/*Allocates a new subMat*/
submat* submat_allocate(spmat* adjMat, expmat *expMat, int* nodes, int n, int numOfVertices);

#endif 