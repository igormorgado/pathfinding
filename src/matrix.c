#include "matrix.h"

gsl_matrix 
*matrix_from_vector(double *vector,
                    size_t  n)
{
    gsl_matrix *M = gsl_matrix_alloc(n, n);
    for(size_t i=0; i < n; i++)
        for (size_t j=0; j < n; j++)
            gsl_matrix_set(M, i, j, vector[i*n+j]);

    return M;
}
