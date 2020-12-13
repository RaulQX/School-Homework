#include <stdio.h>
#include <stdlib.h>

static int cmpnr(const void *p1, const void *p2)
{
    double *a = (double *)p1;
    double *b = (double *)p2;

    return *a - *b;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <num1 num2...> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i;
    int j;
    double array[argc - 1];

    for (i= 1; i < argc; i++)
        array[i-1] = atof(argv[i]);

    qsort (array, argc - 1, sizeof(double), cmpnr);
        for (j = 0; j < argc - 1; j++)
            printf("%lf ", array[j]);

    putchar('\n');

    return 0;
}
