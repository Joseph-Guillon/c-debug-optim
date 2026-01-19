#ifndef DATASET_H
#define DATASET_H

#include <stddef.h>

typedef struct
{
    size_t n;
    double *x;
    double *y;
} Dataset;

Dataset dataset_generate(size_t n, unsigned seed);
void dataset_destroy(Dataset *ds);

#endif
