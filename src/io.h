#ifndef __IO_H__
#define __IO_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t read_matrix_file(char *fname, double **vector);

#endif /* __IO_H__ */
