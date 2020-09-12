#include "linkedlist.h"

/*Utilities functions*/

#define EPSILON 0.00001

/*Prints error message and exits with errorNumber */
void traceAndExit(int errorNum, char* message);

/* Allocates memory on heap of size n * sizeof(DATA) and returns pointer,
* if memory allocation failed, exits program */
void* allocate_memory(int len, size_t size);


