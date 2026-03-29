void cblas_dgemm(char* q,
    int w,
    int e,
    int m,
    int n,
    int k,
    const double alpha,
    const double* A,
    const int lda,
    const double* B,
    const int ldb,
    const double beta,
    double *C,
    const int ldc) {

    for (int i = 0; i   < n; i++) {
        for (int j = 0; j < n; j++) {
            double row_x_coloumn = 0; // var for intermidiate result
            for (int k = 0; k < n;k++) {
                row_x_coloumn += A[i * n + k] * A[k * n + j]; // calc row mul col
            }
            C[i*n + j] = row_x_coloumn;
        }

    }
}