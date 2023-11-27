#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

//Definieren Matrizen über Struct
typedef struct MatrixD {
    size_t z, s;
    double **eintraege;
}MatrixD;

//Funktion zur Definition einer Matrix:
MatrixD MatrixDefi(size_t z, size_t s) {
    MatrixD* matrix = (MatrixD*)malloc(sizeof(struct MatrixD)); //Speicher allozieren für die Matrix
    if (!matrix) {
        // Abfangen, wenn kein Speicher reserviert werden kann
        return (MatrixD) {0};
    }
    matrix->z = z;
    matrix->s = s;

    matrix->eintraege = (double**) malloc(z* sizeof(double*) + s*z*sizeof(double));
    /*(Speicher reservieren für die Einträge)*/
    if(!matrix->eintraege){
        //Abfangen, wenn kein Speicher reserviert werden kann
        free(matrix);
        return (MatrixD) {0};
    }

    for (size_t i=0; i < z; i++){ //Pointer auf Zeilen initialisieren, um die Matrixeinträge richtig zuzuweisen
        matrix->eintraege[i] = (double*)(matrix->eintraege + z) + i*s;
    }
    return *matrix;
}

//Funktion zur Ausgabe der Matrix
void MatrixAusg(const MatrixD *matrix){
    size_t i;
    size_t k;
    for (i=0; i< (matrix->z); i++) {
        for(k=0; k< (matrix->s); k++) {
            printf("%lf ", matrix->eintraege[i][k]);
        }
        printf("\n");
    }
}

/*Funktion ratCholDec aus Aufgabe 25(i):*/
void ratCholDec(int n, MatrixD *A) {
    for(size_t k=0; k<n; k++) { //Schleife Eins; Iteriert über Spalten
        double sum1 = 0;
        for(int j=0; j< ((long)k-1); j++){
            sum1 += A->eintraege[k][j] * A->eintraege[k][j] * A->eintraege[j][j]; //Berechnung der Summe für die Diagonaleinträge
        }
        A->eintraege[k][k] -= sum1; //Berechnung der Diagonaleinträge

        if((A->eintraege[k][k]) < DBL_EPSILON) {
            /*(°) Abfangen, wenn Matrix nicht invertierbar ist
            (Diagonaleinträge pos. <=> symm. Matrix invertierbar)*/
            printf("Matrix nicht invertierbar, Cholesky-Zerlegung nicht durchfuehrbar.");
            exit(EXIT_FAILURE);
        }

            for (size_t i = k + 1; i < n; i++) { //Schleife Zwei; Iteriert über Zeilen
                double sum2 = 0;
                for(int j=0; j< ((long)k-1); j++) {
                    /*Berechnung der Summe für die Einträge unten links (Einträge von L)*/
                    sum2 += A->eintraege[i][j] * A->eintraege[k][j] * A->eintraege[j][j];
                }
                A->eintraege[i][k] = (A->eintraege[i][k] - sum2) / A->eintraege[k][k];
                /*Berechnung der L-Einträge
            Insbesondere existiert (1/A.eintraege[k][k], da das Programm sonst schon vorher beendet
            worden wäre. (Siehe (°))*/

        }
    }
}

/*Kopiere A,b , führe den ganzen Algo mit der Kopie durch*/

/*Funktion SolveRatChol Aus Aufgabe 25(ii):*/
void SolveRatChol(const MatrixD *A, MatrixD *b){ //Matrix A und Vektor b sollen übergeben werden

    MatrixD LD = *A;

    /*Lösen Ly=b*/
    for(size_t i=0; i<LD.z; i++){ //Äußere Schleife, iteriert über Zeilen
        double sum3 = 0;
        for (size_t j= 0; j<i; j++){ //Innere Schleife, iteriert über Spalten (bis vor das jw. Diagonalelement)
            sum3 += LD.eintraege[i][j] * b->eintraege[j][0];
        }
        //Errechnen die Lösung und überschreiben b damit
        b->eintraege[i][0] = (b->eintraege[i][0] - sum3);
    }

    /*Lösen Dz=y*/
    for(size_t i=0; i < (LD.z); i++){
        //Teilen jeden b-Eintrag durch den jw. Diagonaleintrag von D
        b->eintraege[i][0] /= LD.eintraege[i][i];
    }
    printf("Test1\n");
    /*Lösen (L^T)x=z*/
    for(int i = (int)(LD.z)-1; i>=0 ; i--) { //Äußere Schleife, iteriert über Zeilen
        double sum4 = 0;
        printf("Test2\n");

        for(int j = (int)(LD.s); j>i ; j--) { /*Innere Schleife, iteriert über Spalten
            (Beginnend erst nach dem jw. Diagonalelement) */
            sum4 += LD.eintraege[j][i] * b->eintraege[j][0];
        }
        b->eintraege[i][0] -= sum4;

    }
}