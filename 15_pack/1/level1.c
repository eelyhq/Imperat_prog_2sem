
#include "myblas.h"
#include <string.h>

//скопировать вектор из X в Y
void dcopy (int n , const double *X , double *Y ){
  memcpy(Y, X, sizeof(double) * n);
  return;
}
//обменять местами содержимое векторов X и Y
void dswap (int n , double *X , double *Y ){
  double tmp[n];
  memmove(tmp, X, sizeof(double) * n);
  memcpy(X, Y, sizeof(double) * n);
  memcpy(Y, tmp, sizeof(double) * n);
  return;
}
//домножить вектор X на коэффициент alpha
void dscal (int n , double alpha , double *X ) {
  for (int i = 0; i < n; i++) {
    X[i] *= alpha;
  }
  return;
}
//прибавить к вектору Y вектор X, умноженный на коэффициент alpha
void daxpy (int n , double alpha , const double *X , double *Y ) {
  double X_tmp[n];
  dcopy(n, X, X_tmp);
  dscal(n, alpha, X_tmp);

  for (int i = 0; i < n; i++) {
    Y[i] += X_tmp[i];
  }
}
//вычислить скалярное произведение векторов X и Y
double ddot (int n , const double *X , const double * Y ) {
  double res = 0;

  for (int i = 0; i < n; i++) {
    res += X[i] * Y[i];
  }

  return res;
}
