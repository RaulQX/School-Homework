#include <stdio.h>
#include <stdlib.h>

void print_header(FILE *fp, int n, int m)
{
    fprintf(fp, "P3\n");
    fprintf(fp,"%d %d\n255\n", n, m);

}

void format_gradient_black(int n, int m, double divider, FILE *fp)
{
    print_header(fp,n,m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            fprintf(fp,"%f %f %f    ", j/divider, j/divider, j/divider);
        fprintf(fp,"\n");
    }
}

void format_gradient_violet(int n, int m, double divider, FILE *fp)
{
    print_header(fp,n,m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            fprintf(fp,"%f 0 %f    ", j/divider, j/divider);
        fprintf(fp,"\n");
    }
}

int main()
{
    int n = 1000;
    int m = 1000;

    double divider = m/255.0;

    FILE *fp = fopen("Gradient_Black_1000x1000.ppm", "w");
    if (!fp)
    {
        printf("Couldn't create file\n");
        exit(1);
    }

    format_gradient_black(n, m, divider, fp);

    fclose(fp);

    FILE *fp2 = fopen("Gradient_Violet_1000x1000.ppm", "w");
    if (!fp)
    {
        printf("Couldn't create file\n");
        exit(2);
    }

    format_gradient_violet(n, m, divider, fp2);

    fclose(fp2);


    return 0;
}
