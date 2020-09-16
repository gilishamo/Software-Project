#ifndef _EXPMAT_H
#define _EXPMAT_H

/* Struct to hold the matrix that describes the expected number of edges between each 
 * vetex i and j of the original graph */

typedef struct _expmat {
	int* degreeOfVertex; /*degreeOfVertex[i] == degree of vertex i in the original graph*/
	int sumOfDegrees; /*Sum of degree of each vertex in the original graph*/

	/* Frees all resources used by mat, excluding resources that were pre allocated */
	void (*free)(struct _expmat* mat);

	/* Adds degree of vertex i it the graph. Called
	 * exactly numOfVertices times in order (i = 0 to numOfIndices-1) , after n times sumOfDegrees is initialized*/
	void (*add_degree)(struct _expmat* mat, double degree, int indexOfVertex);

	/* Return the degree of vertex i (i is the index in the original grpah)*/ 
	int (*getDegree)(struct _expmat* mat, int i);

	/* Return the expected number of edges between vertex i and vertex j
	 * where i and j are the indices of the vertices in the original grpah */
	double (*getExpNumOfEdges)(struct _expmat* mat, int i, int j);

	/* Multiplies matrix mat by vector vector, into result (result is pre-allocated) 
	 *  by passing the argument verticesOfSub,  mat is the matrix that describes the expected number 
     * of edges between each vetex i and j of the sub graph */
	void (*mult)(struct _expmat* mat, int* verticesOfSub, int sizeOfSub, const double* vector, double* result);

}expmat;

/* Allocates a new expmat with matrix of size numOfVertices */
expmat* allocate_expmat(int numOfVertices);

#endif