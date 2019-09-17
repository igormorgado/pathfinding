#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "defs.h"

gsl_matrix *matrix_from_vector(double *vector, size_t n);

#endif /* __MATRIX_H__ */

