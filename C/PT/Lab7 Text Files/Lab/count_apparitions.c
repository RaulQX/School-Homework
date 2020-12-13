#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

void read_stdin(int *apparitions)
{
    int c;
    while ((c=fgetc(stdin)) != EOF)
        apparitions[c]++;
}

void print_frequencies(int *array, int n)
{
    for (int i=0; i<n; i++)
        if (array[i])
            fprintf(stdout, "%c: %d\n", i, array[i]);
}


int main()
{
    int apparitions [N];

    memset(apparitions, 0, sizeof(int)*256);
    read_stdin(apparitions);

    print_frequencies(apparitions, N);
}
