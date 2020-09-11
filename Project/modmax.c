#include <stdlib.h>
#include "arraylist.h"
#include "submat.h"
#include "modmax.h"
#include "util.h"

#define EPSILON 0.00001

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
            maxScoreIndex = calcScore(score, division, unmoved, n, modulMat); /* i'm not sure if I send division right */
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
    int j, numOfNodes = modulMat->numOfNodes, k, maxIndex, first = 1; /* k is the node's number in unmoved*/
    double valA, valD, sum, value, max; /* the value of score[k] */
    spmat* A = modulMat->adjMat;
    double* D = modulMat->expMat;

    for (k = 0; k < n; k++) {
        /* if unmoved[k] == -1 than k isn't in unmoved */
        if (unmoved[k] != -1) {
            division[k] = -division[k];
            /* calculation of value: */
            sum = 0;
            for (j = 0; j < n; j++) {
                valA = (*A->getVal)(A, k, j);
                valD = *(D + (k * numOfNodes) + j);
                sum += ((valA - valD) * division[j]);
            }
            value = (4 * division[k] * sum) + (4 * *(D + (k * numOfNodes) + k)); /* make sure it's correct */
            score[k] = value;
            if (first) {
                max = value;
                maxIndex = k;
                first = 0;
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
