#ifndef METRICS_H
#define METRICS_H

#include "dataset.h"

typedef struct
{
    double mean_x;
    double mean_y;
    double std_x;
    double std_y;
} Summary;

Summary metrics_summary(const Dataset *ds);

double metrics_pairwise_score(const Dataset *ds, int repeat);

#endif
