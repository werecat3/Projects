// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"



// Module-level variables:

float result_matrix[3][3] = {{},{},{}};
float result_matrix_2[2][2] = {{1, 2},{2, 4}};
float test_matrix[3][3] = {{1, 2, 3}, {7, 8, 9}, {4, 5, 6}};
float test_matrix_1[3][3] = {{1, 2, 3}, {7, 8, 9}, {4, 5, 6}};
float test_matrix_2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 1}};
float test_matrix_3[3][3] = {{2, 3, 4}, {8, 9, 10}, {5, 6, 7}};
float test_matrix_4[3][3] = {{56.01, 57.01, 58.01}, {62.01, 63.01, 64.01}, {59.01, 60.01, 61.01}}; //this is an answer too just bad positioning
float test_matrix_5[3][3] = {{2.2, 1, 4}, {8.3, 5.4, 5}, {6, 7, 8}};
float test_matrix_6[3][3] = {{20, 5, 7}, {1, 5, 7}, {56, 2, 9}};
float test_matrix_7[3][3] = {{1.5, 5, 2}, {7, 5, 2.3}, {1, 2, 3}};
//----------below this are the answers that I compare functions to
float test_matrix_add[3][3] = {{3, 5, 7}, {12, 14, 16}, {12, 14, 7}};
float test_matrix_add_2[3][3] = {{3.2, 3, 7}, {15.3, 13.4, 14} , {10, 12, 14}};
float test_matrix_multiply[3][3] = {{2, 4, 6}, {14, 16, 18} , {8, 10, 12}};
float test_matrix_multiply_2[3][3] = {{5.5, 11, 16.5}, {38.5, 44, 49.5} , {22, 27.5, 33}};
float test_matrix_transpose[3][3] = {{1, 7, 4}, {2, 8, 5}, {3, 9, 6}};
float test_matrix_transpose_2[3][3] = {{2.2, 8.3, 6}, {1, 5.4, 7}, {4, 5, 8}};
float result_matrix_of_mult[3][3] = {{36, 42, 21}, {126, 150, 93}, {81, 96, 57}};
float result_matrix_of_mult_2[3][3] = {{36.8, 32.8, 38}, {135.8, 113.2, 140}, {86.3, 73, 89}};
float result_matrix_submatrix[2][2] = {{8, 9}, {5, 6}};
float result_matrix_submatrix_2[2][2] = {{1, 2}, {4, 5}};
float result_matrix_inverse[3][3] = {{.05, -.05, 0}, {.65, -.35, -.23}, {-.47, .407, .161}};
float result_matrix_inverse_2[3][3] = {{-.17, .18, -.025}, {.31, -.041, -.17}, {-.15, -.033, .45}};

float trace();
int truth_value;
int counter = 0;
int main()
{
    BOARD_Init();

    printf("Beginning of Jrschlos's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    printf("%c", 10);
    
    //showing matrix print works
    printf("Expected output MatrixPrint():\n");
    printf("| 1.00 | 2.00 | 3.00 |\n| 7.00 | 8.00 | 9.00 |\n| 4.00 | 5.00 | 6.00 |\n");
    printf("\nOutput from MatrixPrint function:\n");
    MatrixPrint(test_matrix);
    
    
    //showing matrix equals works
    if (MatrixEquals(test_matrix, test_matrix_1) == 0) {
        printf("False, if this happens something is wrong lol\n");
    }
    else {
        truth_value += 1; //expects to be true so adds to the amount passed
    }
    
    if (MatrixEquals(test_matrix, test_matrix_2) == 0) {
        truth_value += 1; //expects to be false so adds to the amount passed
    }
    else {
    }
    printf("Passed (%d/2): MatrixEquals()\n", truth_value);
    truth_value = 0;
    
    //showing matrix scalar add works
    MatrixScalarAdd(55.01, test_matrix, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_4) == 1) {
        truth_value += 1;
    }
    
    MatrixScalarAdd(1, test_matrix, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_3) == 1) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixScalarAdd()\n", truth_value);
    truth_value = 0;
    
    //showing matrix add works
    MatrixAdd(test_matrix, test_matrix_2, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_add) == 1) {
        truth_value += 1;
    }
    
    MatrixAdd(test_matrix, test_matrix_5, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_add_2) == 1) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixAdd()\n", truth_value);
    truth_value = 0;
    
    //showing matrix multiply scalar works
    MatrixScalarMultiply(2, test_matrix, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_multiply) == 1) {
        truth_value += 1;
    }
    
    MatrixScalarMultiply(5.5, test_matrix, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_multiply_2) == 1) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixScalarMultiply()\n", truth_value);
    truth_value = 0;
    
    //showing matrix multiply works
    MatrixMultiply(test_matrix, test_matrix_2, result_matrix);
    if (MatrixEquals(result_matrix, result_matrix_of_mult) == 1){
        truth_value += 1;
    }
    
    MatrixMultiply(test_matrix, test_matrix_5, result_matrix);
    if (MatrixEquals(result_matrix, result_matrix_of_mult_2) == 1){
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixMultiply()\n", truth_value);
    truth_value = 0;
    
    //showing matrix trace works
    if (abs(MatrixTrace(test_matrix_3) - 18) < FP_DELTA) {
        truth_value += 1;
    }
    
    if (abs(MatrixTrace(test_matrix_5) - 15.6) < FP_DELTA) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixTrace()\n", truth_value);
    truth_value = 0;
    
    //showing Matrix Transpose works
    MatrixTranspose(test_matrix, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_transpose) == 1) {
        truth_value += 1;
    }
    
    MatrixTranspose(test_matrix_5, result_matrix);
    if (MatrixEquals(result_matrix, test_matrix_transpose_2) == 1) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixTranspose()\n", truth_value);
    truth_value = 0;
    
    //showing submatrix function works
    MatrixSubmatrix(0, 0, test_matrix, result_matrix_2);
    if (abs(result_matrix_2[0][0] - result_matrix_submatrix[0][0]) < FP_DELTA) { //need to be able to test two x two matrixs
        counter += 1;
    }
    if (abs(result_matrix_2[0][1] - result_matrix_submatrix[0][1]) < FP_DELTA) {
        counter += 1;
    }
    if (abs(result_matrix_2[1][0] - result_matrix_submatrix[1][0]) < FP_DELTA) {
        counter += 1;
    }
    if (abs(result_matrix_2[1][1] - result_matrix_submatrix[1][1]) < FP_DELTA) {
        counter += 1;
    }
    if (counter == 4) {
        truth_value += 1;
    }
    counter = 0;
    
    //Showing the sub matrix function works
    MatrixSubmatrix(1, 2, test_matrix, result_matrix_2);
    if (abs(result_matrix_2[0][0] - result_matrix_submatrix_2[0][0]) < FP_DELTA) { //need to be able to test two x two matrixs
        counter += 1;
    }
    if (abs(result_matrix_2[0][1] - result_matrix_submatrix_2[0][1]) < FP_DELTA) {
        counter += 1;
    }
    if (abs(result_matrix_2[1][0] - result_matrix_submatrix_2[1][0]) < FP_DELTA) {
        counter += 1;
    }
    if (abs(result_matrix_2[1][1] - result_matrix_submatrix_2[1][1]) < FP_DELTA) {
        counter += 1;
    }
    if (counter == 4) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixSubmatrix()\n", truth_value);
    truth_value = 0;
    
    //showing the determinant function works
    if (MatrixDeterminant(test_matrix) == 0) {
        truth_value += 1;
    }
    if (MatrixDeterminant(test_matrix_5) - 84.44 < FP_DELTA) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixDeterminant()\n", truth_value);
    truth_value = 0;
    
    //Showing the inverse function works correctly.
    MatrixInverse(test_matrix_6, result_matrix);
    if (MatrixEquals(result_matrix, result_matrix_inverse) == 1) {
        truth_value += 1;
    }
    
    MatrixInverse(test_matrix_7, result_matrix);
    if (MatrixEquals(result_matrix, result_matrix_inverse_2) == 1) {
        truth_value += 1;
    }
    printf("Passed (%d/2): MatrixInverse()\n", truth_value);
    

    // Add more tests here!
    BOARD_End();
    while (1);
}

