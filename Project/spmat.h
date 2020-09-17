#ifndef _SPMAT_H
#define _SPMAT_H

typedef struct _spmat {
	/* Matrix size (n*n) */
	int		n;

	/* Adds row i the matrix. Called
	 * exactly n times in order (i = 0 to n-1) */
	void	(*add_row)(struct _spmat* A, const double* row, int i);

	/* Frees all resources used by A */
	void	(*free)(struct _spmat* A);

	/* Multiplies matrix A by vector v, into result (result is pre-allocated) */
	void	(*mult)(const struct _spmat* A, const double* v, double* result, int* vertices, int len);

	/* Returns the value in row i and column j of the original matrix*/
	double	(*getVal)(struct _spmat* mat, int i, int j);

	double (*multRowInVec)(const struct _spmat* A, int row, const double* vector, int* vertices, int sizeOfSub);

	/* Private field for inner implementation.
	 * Should not be read or modified externally */
	void* private;
} spmat;

/* Allocates a new arrays sparse matrix of size n with nnz non-zero elements */
spmat* spmat_allocate_array(int n, int nnz);

/* Calls add_row n times in order*/ 
void readMatrixFileToSpmat(spmat* spmat, char* fileName);

#endif