#include "spmat.h"


/*Struct that holds the values of modularity matrix B[g] bar */

typedef struct _submat {
	/*sub graph containes nodes nodes[0], nodes[1],..*/
	int* nodes;

	/*num of nodes in the sub graph*/
	int sizeOfSub;

	/*num of nodes in the original graph*/
	int numOfNodes;

	/*pointers to the original matrix B = adjMat + expMat*/
	spmat* adjMat;
	double* expMat;

	/* f[i] == sum of row i in modularity matrix B[g]*/
	double* f;

	double	(*getVal)(struct _submat* mat, int i, int j);

	/* Frees all resources used by mat */
	void	(*free)(struct _submat* mat);

	/* Multiplies matrix mat by vector vector, into result (result is pre-allocated) */
	void	(*mult)(struct _submat* mat, const double* vector, double* result);

}submat;

/*Allocates a new subMat*/
submat* submat_allocate(submat* adjMat, double *expMat, int* nodes, int n, int numOfNodes);
