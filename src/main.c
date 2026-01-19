#include <stdio.h>
#include <stdlib.h>

#include "dataset.h"
#include "metrics.h"

static size_t parse_size(const char *s, const char *name)
{
    char *end = NULL;
    long v = strtol(s, &end, 10);
    if (!end || *end != '\0' || v <= 0)
    {
        fprintf(stderr, "Invalid %s: %s\n", name, s);
        exit(2);
    }
    return (size_t)v;
}

int main(int argc, char **argv)
{
    size_t n = 2000;
    int repeat = 3;

    if (argc >= 2)
        n = parse_size(argv[1], "n");
    if (argc >= 3)
        repeat = (int)parse_size(argv[2], "repeat");

    printf("Generating dataset (n=%zu)\n", n);
    Dataset ds = dataset_generate(n, 123u);

    Summary s = metrics_summary(&ds);
    printf("Summary: mean_x=%.6f std_x=%.6f | mean_y=%.6f std_y=%.6f\n",
           s.mean_x, s.std_x, s.mean_y, s.std_y);

    printf("Computing pairwise score (repeat=%d)...\n", repeat);
    double score = metrics_pairwise_score(&ds, repeat);
    printf("Score = %.6f\n", score);

    dataset_destroy(&ds);
    return 0;
}
