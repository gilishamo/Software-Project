#include <stdlib.h>
#include <stdio.h>
#include "util.h"

void traceAndExit(int errorNum, char* message) {
	printf("Erorr is: %s", message);
	exit(errorNum);
}


void* allocate_memory(int len, size_t size) {
	void* pointer;

	pointer = malloc(len * size);
	if (pointer == NULL) {
		traceAndExit(2, "failed to allocate memory.");
	}

	return pointer;
}

