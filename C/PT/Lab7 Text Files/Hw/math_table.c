#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void draw_antet(FILE *fp)
{
    fprintf(fp, "============================================================\n");
    fprintf(fp, "Degrees   Radians   sin(x)   cos(x)   tan(x)   ctan(x)\n");
    fprintf(fp, "============================================================\n");
}

float to_degrees(float radians)
{
    return ((180*radians)/M_PI);
}

void format_file(FILE *fp, char **argv)
{
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    int n = atoi(argv[4]);
    float step = (b - a)/(n-1.0);

    draw_antet(fp);

    float rad=a;
    float degrees;
    float tang;
    float ctan;

    for (int i = 0; i < n; i++)
    {
        degrees = to_degrees(rad);

        fprintf(fp, "%.3f   ", to_degrees(rad));
        if (degrees < 100 && degrees > 0)
            fprintf(fp," ");
        if (degrees < 10 && degrees > -10)
            fprintf(fp," ");
        if (fabs (degrees) < 1e-3)
            fprintf(fp,"  ");

        if (rad > 0 && rad < 10)
            fprintf(fp," ");
        fprintf(fp, "%.3f   ", rad);

        if (sin(rad) > 0)
            fprintf(fp," ");
        fprintf(fp, "%.3f   ", sin(rad));

        if (cos(rad) > 0)
            fprintf(fp, " ");
        fprintf(fp, "%.3f   ", cos(rad));

        if (fabs(cos(rad)) <= 1e-3)
            fprintf(fp, "   -   ");
        else
        {
            tang = tan(rad);
            if (tang>0)
                fprintf(fp," ");
            if (tang < 10 && tang > -10)
                fprintf(fp," ");
            fprintf(fp, "%.3f   ", tang);
        }

        if (fabs(tang) <= 1e-3)
            fprintf(fp, "   -   ");
        else
        {
            ctan= 1.0/tang;
            if (ctan < 10 && ctan > 0)
                fprintf(fp," ");
            if (ctan > 10)
                fprintf(fp, " ");
            fprintf(fp, "%.3f   ", ctan);
        }

        fprintf(fp, "\n");
        rad+=step;
    }
}

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        printf("Please give as command line arguments the name of the file, the interval [a b] and"
               " the number of calculated values as such:\n");
        printf("<file name> <a> <b> <n>\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "w");
    if (!fp)
    {
        printf("Error opening file\n");
        exit(2);
    }

    format_file(fp, argv);

    fclose(fp);

    return 0;
}
