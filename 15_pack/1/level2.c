#include "myblas.h"
#include <string.h>

//вычислить вектор (alpha*A*X + beta*Y) длины m, и записать его в Y
//здесь A –- матрица размера m на n, X –- вектор длины n, а Y –- вектор длины m
void dgemv (
int m , int n ,
double alpha , const double *A , const double *X ,
double beta , double * Y
) {
    double tmp_x[n];
    memcpy(tmp_x, X, sizeof(double) * n);
    dscal(n, alpha, tmp_x);

    double one_more_tmp_x[m];
    for (int i = 0; i < m;i++) {
        double res = 0;
        for (int j = 0; j < n; j++) {
            res += A[i * n + j] * tmp_x[j];
        }
        one_more_tmp_x[i] = res;
    }

    dscal(m, beta, Y);

    for (int i = 0; i < m; i++) {
        Y[i] += one_more_tmp_x[i];
    }
}
//вычислить матрицу (alpha*X*Yt + A) и записать её в A
//здесь Yt –- это транспонированный вектор Y, то есть записанный как вектор-строка
// A –- матрица размера m на n, X –- вектор длины m, а Y –- вектор длины n
void dger (
int m , int n ,
double alpha , const double *X , const double *Y ,
double * A
) {
    for (int i = 0; i < m;i++) {
        for (int j = 0; j < n;j++) {
            A[i*n + j] += X[i] * Y[j] * alpha;
        }
    }
}