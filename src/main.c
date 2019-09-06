#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "defs.h"
#include "io.h"

gsl_matrix *matrix_from_vector(double *vector, size_t n);

gsl_matrix *matrix_from_vector(double *vector, size_t n)
{
    gsl_matrix *M = gsl_matrix_alloc(n, n);
    for(size_t i=0; i < n; i++)
        for (size_t j=0; j < n; j++)
            gsl_matrix_set(M, i, j, vector[i*n+j]);

    return M;
}


int main(int argc, char *argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        exit(1);
    } 

    char *fname = argv[1];
    double *vector = malloc(sizeof * vector);
    size_t n = read_matrix_file(fname, &vector);
    gsl_matrix *M = matrix_from_vector(vector, n);
    free(vector);

    printf("Max V: %d  E: %d\n", MAX_VERTICES, MAX_EDGES);

    gsl_matrix_fprintf(stdout, M, "%.2f");


    gsl_matrix_free(M);

    return 0;
}
