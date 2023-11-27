#include "chllib.h"

void freeMatrix(MatrixD A) {
    for (size_t i = 0; i < A.z; i++) {
        free(A.eintraege[i]);
    }
    free(A.eintraege);
}

int main() {
    MatrixD A = MatrixDefi(4,4);
    A.eintraege[0][0] = 1;      A.eintraege[0][1] =  0;      A.eintraege[0][2] = 0;     A.eintraege[0][3] = 0;
    A.eintraege[1][0] = 0;      A.eintraege[1][1] =  1;      A.eintraege[1][2] = 0;     A.eintraege[1][3] = 0;
    A.eintraege[2][0] = 0;      A.eintraege[2][1] =  0;      A.eintraege[2][2] = 1;     A.eintraege[2][3] = 0;
    A.eintraege[3][0] = 0;      A.eintraege[3][1] =  0;      A.eintraege[3][2] = 0;     A.eintraege[3][3] = 1;

    MatrixD b = MatrixDefi(4,1);
    b.eintraege[0][0] = 2;
    b.eintraege[0][0] = 7;
    b.eintraege[0][0] = 7;
    b.eintraege[0][0] = 1;

    ratCholDec(4, &A);
    SolveRatChol(&A,&b);
    MatrixAusg(&b);
    freeMatrix(A);
    }