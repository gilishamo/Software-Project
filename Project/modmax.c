#include <stdlib.h>
#include <stdio.h>
#include "submat.h"
#include "modmax.h"
#include "util.h"

int calcScore(double*, double*, int*, int, submat*);

void modularityMaximization(double* division, int n, submat* modulMat) {
    int i,j, maxScoreIndex, maxImproveIndex;
    int* unmoved;
    double * score, * indices, * improve, maxImprove, deltaQ;

    improve = (double*)allocate_memory(n, sizeof(double));
    indices = (double*)allocate_memory(n, sizeof(double));
    unmoved = (int*)allocate_memory(n, sizeof(int));
    score = (double*)allocate_memory(n, sizeof(double));

    do{ 
        /* initializes Unmoved */
        for (i = 0; i < n; i++) {
            unmoved[i] = i;
        }
       

        for (i = 0; i < n; i++) {
            /*computing deltaQ for the move of eachh unmoved vertex i 
             * and storing the result in score[i] */
            maxScoreIndex = calcScore(score, division, unmoved, n, modulMat);
            division[maxScoreIndex] = -division[maxScoreIndex];
            indices[i] = maxScoreIndex;
            if (i == 0) {
                improve[i] = score[maxScoreIndex];
                maxImprove = improve[i];
                maxImproveIndex = i;
            }
            else {
                improve[i] = improve[i-1] + score[maxScoreIndex];
                if (maxImprove < improve[i]) {
                    maxImprove = improve[i];
                    maxImproveIndex = i;
                }
            }
            unmoved[maxScoreIndex] = -1;
        }

        for (i = n-1; i > maxImproveIndex; i--) {
            j = indices[i];
            division[j] = -division[j];
        }

        if(maxImproveIndex == n-1) {
            deltaQ = 0;
        }
        else {
            deltaQ = improve[maxImproveIndex];
        }
        
    } while(deltaQ > EPSILON);

    free(score);
    free(unmoved);
    free(indices);
    free(improve);

    return;
}

/* calculates (and updates) the vector score for every k in unmoved */
int calcScore (double* score, double* division, int* unmoved, int n, submat* modulMat) {
    int k, maxIndex = -1, * vertices = modulMat->vertices; /* k is the node's number in unmoved*/
    double valA, valD, sum, max, value; /* the value of score[k] */
    spmat* A = modulMat->adjMat;
    expmat* D = modulMat->expMat;

    for (k = 0; k < n; k++) {
        /* if unmoved[k] == -1 than k isn't in unmoved */
        if (unmoved[k] != -1) {
            sum = 0;
            division[k] = -division[k];

            valA = (*A->multRowInVec)(A, vertices[k], division, vertices, n);
            valD = (*D->multRowInVec)(D, vertices[k], division, vertices, n);
            sum = valA - valD;

            value = (4 * division[k] * sum) + 4 * (*D->getExpNumOfEdges)(D, vertices[k], vertices[k]);
            score[k] = value;

            if (maxIndex == -1) {
                max = value;
                maxIndex = k;
            }
            else if(value > max) {
                max = value;
                maxIndex = k;
            }

            division[k] = -division[k];
        }
    }
    return maxIndex;
}
