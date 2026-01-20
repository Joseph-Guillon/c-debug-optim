#include "metrics.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static double mean(const double *a, size_t n)
{
    double s = 0.0;
    for (size_t i = 0; i < n; ++i)
        s += a[i];
    return s / (double)n;
}

static double stddev(const double *a, size_t n, double m)
{
    double v = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        double d = a[i] - m;
        v += d * d;
    }
    return sqrt(v / (double)n);
}

Summary metrics_summary(const Dataset *ds)
{
    Summary out;
    out.mean_x = mean(ds->x, ds->n);
    out.mean_y = mean(ds->y, ds->n);
    out.std_x = stddev(ds->x, ds->n, out.mean_x);
    out.std_y = stddev(ds->y, ds->n, out.mean_y);
    return out;
}

double metrics_pairwise_score(const Dataset *ds, int repeat){
    size_t n = ds->n;
    double total = 0.0; 
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
                double d = ds->x[i]-ds->y[i] - (ds->x[j]-ds->y[j]);
                total += sin(d) * d;
        }
    }
    total = total*repeat;
    return total / (double)(repeat * (double)n * (double)n);
}
