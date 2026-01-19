#include "dataset.h"

#include <stdlib.h>
#include <stdio.h>

Dataset dataset_generate(size_t n, unsigned seed)
{
    Dataset ds;
    ds.n = n;

    ds.x = (double *)malloc(n * sizeof(double));
    if (!ds.x)
    {
        fprintf(stderr, "malloc failed for x\n");
        exit(1);
    }

    srand(seed);
    for (size_t i = 0; i < n; ++i)
    {
        ds.x[i] = (double)(rand() % 1000) / 1000.0;
        ds.y[i] = (double)(rand() % 1000) / 1000.0;
    }

    return ds;
}

void dataset_destroy(Dataset *ds)
{
    if (!ds)
        return;

    free(ds->x);
    ds->x = NULL;
    ds->y = NULL;
    ds->n = 0;
}
