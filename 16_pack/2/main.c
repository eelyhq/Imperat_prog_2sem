#include <assert.h>
#include "cblas.h"

// void cblas_dgemm(char* q,
//     char* w,
//     char* e,
//     int m,
//     int n,
//     int k,
//     const double alpha,
//     const double* A,
//     const int lda,
//     const double* B,
//     const int ldb,
//     const double beta,
//     double *C,
//     const int ldc) {
//
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             int row_x_coloumn = 0; // var for intermidiate result
//             for (int k = 0; k < n;k++) {
//                 row_x_coloumn += A[i * n + k] * A[k * n + j]; // calc row mul col
//             }
//             C[i*n + j] = row_x_coloumn;
//         }
//
//     }
//
// }
//
// void MatrixSqr ( int n , const double *A , double * R ) {
//     cblas_dgemm("CblasRowMajor", "CblasNoTrans", "CblasNoTrans",
//             n, n, n, 1.0, A, n, A, n, 1.0, R, n);
//     return;
// }



void MatrixSqr ( int n , const double *A , double * R );

int main () {
    double A [3][3] = {{0 ,1 ,2} ,{2 ,0 ,0} ,{3 ,0 ,1}};
    double R [3][3];
    MatrixSqr (3 , & A [0][0] , & R [0][0]);
    assert ( R [0][0] == 8 && R [0][1] == 0 && R [0][2] == 2);
    assert ( R [1][0] == 0 && R [1][1] == 2 && R [1][2] == 4);
    assert ( R [2][0] == 3 && R [2][1] == 3 && R [2][2] == 7);
    return 0;
}