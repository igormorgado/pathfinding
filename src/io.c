#include "io.h"

/*
 * Read the matrix file as specified and store all distances in
 * a vector of doubles.
 *
 * Returns the order of matrix as an integer, 0 on failure.
 *
 */
size_t read_matrix_file(char *fname, double **p_vector)
{
    /* Check if file exists */
    if(access(fname, F_OK) == -1) {
        perror("access");
        return(0);
    }

    /* Try to open file */
    FILE *fd = fopen(fname, "r");
    if (fd == NULL) {
        perror("fopen: ");
        return(0);
    }

    /* Read the first line as a string*/
    char line[BUFSIZ];
    if (fgets(line, sizeof line, fd) == NULL) {
        perror("fgets");
        return(0);
    }

    /* Find thee order of matrix */
    size_t n;
    if (sscanf(line, "%zu", &n) != 1) {
        perror("sscanf");
        return(0);
    }

    /* Check for valid matrix ranks */
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid matrix size %zu\n", n);
        return(0);
    }

    /* Allocates the array */
    double * t_vector = realloc(*p_vector, n * n * sizeof **p_vector);
    if (t_vector == NULL) {
        perror("realloc");
        return(0);
    }
    *p_vector = t_vector;

    double *vector = *p_vector;

    /* Reads the elements */
    int b;
    for(size_t i=0; i < n; i++) {
        // Read the i-th line into line
        if (fgets(line, sizeof line, fd) == NULL) {
            perror("fgets");
            return(0);
        }

        /* Reads th j-th element of i-th line into the vector */
        char *elem_ptr = line;
        double elem;
        for (size_t j=0; j < n; j++) {
            if(sscanf(elem_ptr, "%lf%n", &elem, &b) != 1) {
                perror("sscanf");
                return(0);
            }
            vector[n*i+j] = elem;
            elem_ptr += b;
        }
    }
    fclose(fd);
    
    return n;
}
