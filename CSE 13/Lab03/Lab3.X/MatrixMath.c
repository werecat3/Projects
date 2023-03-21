#include "MatrixMath.h"
#include <stdio.h>
#include <stdlib.h>

#define DIM2 2

float Determinant2x2(float mat[2][2]);

void MatrixPrint(float mat[3][3]) {
    printf("%c", 10);
    float arrayElementValue; 
    int r, c; 
    int counter;
    for (r = 0; r < DIM; r++) { 
        for (c = 0; c < DIM; c++) { 
            arrayElementValue = mat[r][c]; 
            printf("%c %.2f ", 124, arrayElementValue);
            if (counter % 3 == 0) {
                printf("%c %c", 124, 10);
            }
            counter += 1;
        } 
    }
    printf("%c", 10);
    counter = 0;
}

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            if (abs(mat1[r][c] - mat2[r][c]) < FP_DELTA) {
                continue; 
            }
            else {
                return 0; 
            }
        }
    }
    return 1;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = mat1[r][c] + mat2[r][c];

        }
    }
}



void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    int r, c, k;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = 0;
            for (k = 0; k < DIM; k++){
            result[r][c] +=  mat1[r][k] * mat2[k][c];
            }
        }   
    }
}


void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]){
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = mat[r][c] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = mat[r][c] * x;
        }
    }
}


float MatrixTrace(float mat[3][3]) {
    float trace = 0;
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            if (c == r) {
                trace += mat[r][c];
            }
        }
    }
    return trace;
}

void MatrixTranspose(float mat[3][3], float result[3][3]) {
    int r, c;
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = mat[c][r];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    int r, c;
    int x, y;
    if (i == 0 && j == 0) {
        x = 1;
        for (r = 0; r < 2; r++ ) {
            y = 1;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y]; 
                
                y += 1;
            }
            x += 1;
        }
    }
    if (i == 0 && j == 1) {
        x = 1;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 2;
            }
            x += 1;
        }
    }
    if (i == 0 && j == 2) {
        x = 1;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 1;
            }
            x += 1;
        }
    }
    if (i == 1 && j == 0) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 1;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 1;
            }
            x += 2;
        }
    }
    if (i == 1 && j == 1) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 2;
            }
            x += 2;
        }
    }
    if (i == 1 && j == 2) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 1;
            }
            x += 2;
        }
    }
    if (i == 2 && j == 0) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 1;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 1;
            }
            x += 1;
        }
    }
    if (i == 2 && j == 1) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 2;
            }
            x += 1;
        }
    }
    if (i == 2 && j == 2) {
        x = 0;
        for (r = 0; r < 2; r++ ) {
            y = 0;
            for (c = 0; c < 2; c++) {
                result[r][c] = mat[x][y];
                y += 1;
            }
            x += 1;
        }
    }
 
}

float Determinant2x2(float mat[2][2]) {
    float deter = 0;
    deter = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    return deter;
}

float MatrixDeterminant(float mat[3][3]) {
    float result[2][2] = {{}, {}};
    float total = 0;
    int count = 0;
    int r =0, c;
    for (c = 0; c < 3; c++) {
        MatrixSubmatrix(r, c, mat, result);
        if (count % 2 == 0) {
            total += (mat[r][c] * (Determinant2x2(result)));
        }
        else {
            total -= (mat[r][c] * (Determinant2x2(result)));
        }
        count += 1;
    }
    return total;
}

void MatrixInverse(float mat[3][3], float result[3][3]) {
    int r, c;
    float result_temp[2][2] = {{}, {}};
    float almost_result[3][3] = {{}, {}, {}};
    int count = 0;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            MatrixSubmatrix(r, c, mat, result_temp);
            if (count % 2 == 0) {
                almost_result[r][c] = Determinant2x2(result_temp);
            }
            else {
                almost_result[r][c] = -Determinant2x2(result_temp);
            }
        }
    }
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            result[r][c] = almost_result[r][c] / MatrixDeterminant(mat);
        }
    }
}
