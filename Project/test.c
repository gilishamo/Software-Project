#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void createInputFile(char *fileName, int numOfNodes) {
	FILE* output;
	int k, i, j, currDegree, currIndex = 0;
	int* neighbors;

	output = fopen(fileName, "w");
	assert(output != NULL);

	srand(time(NULL));

	k = fwrite(&numOfNodes, sizeof(int), 1, output);
	assert(k == 1);

	for (i = 1; i <= numOfNodes; i++) {
		k = fwrite(&i, sizeof(int), 1, output);
		assert(k == 1);

		currDegree = rand() % (numOfNodes);

		neighbors = (int*)malloc(currDegree * sizeof(int));
		assert(neighbors != NULL);

		k = fwrite(&currDegree, sizeof(int), 1, output);
		assert(k == 1);

		for (j = 0; j < currDegree; j++) {
			/*generate sub group of index of size currDegree s.t all index are distinct and index != i*/
		}

		free(neighbors);
	}
}