#include <stdio.h>
#include <stdlib.h>

#define MULTIPLIER 300
#define COLORS_IMPLEMENTED 9

char *colors[] = {"blue", "coral", "gold", "red", "mediumvioletred", "orangered", "orchid", "mintcream",
                  "mediumturquoise", "lightgoldenrodyellow"};

typedef struct point
{
    double y;
    double x;
}point;

void sierpinski (point a, point b, point c, point d, unsigned long step, FILE *fp)
{
    // st - stanga; dr - dreapta; s- sus; j - jos
    char color[100];

    if (step == 0)
        return;
    point sus_st;
    point sus_dr;

    point stanga_s;
    point stanga_j;

    point jos_st;
    point jos_dr;

    point dreapta_s;
    point dreapta_j;

    point centru_st_s;
    point centru_st_j;
    point centru_dr_j;
    point centru_dr_s;

    double dx = (d.x - a.x)/3;  //versor for the x axis
    double dy = (b.y - a.y)/3;  //versor for the y axis

    sus_st.y = a.y;
    sus_st.x = dx + a.x;

    sus_dr.y = a.y;
    sus_dr.x = 2*dx + a.x;

    jos_st.y = b.y;
    jos_st.x = dx + a.x;

    jos_dr.y = b.y;
    jos_dr.x = dx + a.x;

    stanga_s.y = dy + a.y;
    stanga_s.x = a.x;

    stanga_j.y = 2 * dy + a.y;
    stanga_j.x = a.x;

    dreapta_j.y = 2 * dy + a.y;
    dreapta_j.x = d.x;

    dreapta_s.y = dy + a.y;
    dreapta_s.x = d.x;

    centru_dr_j.x = 2 * dx + a.x;
    centru_dr_j.y = 2 * dy + a.y;

    centru_dr_s.x = 2 * dx + a.x;
    centru_dr_s.y = dy + a.y;

    centru_st_s.x = dx + a.x;
    centru_st_s.y = dy + a.y;

    centru_st_j.x = dx + a.x;
    centru_st_j.y = 2 * dy + a.y;

    if (step <= COLORS_IMPLEMENTED)
        strcpy(color, colors[step]);
    else
        strcpy(color, "slategray");

    fprintf(fp,"<polyline points=\"%lf,%lf %lf,%lf %lf,%lf %lf,%lf %lf,%lf\" stroke=\"red\" stroke-width=\"0\" fill=\"%s\" />\n",
            centru_st_s.x *MULTIPLIER, centru_st_s.y *MULTIPLIER, centru_st_j.x *MULTIPLIER, centru_st_j.y *MULTIPLIER,
            centru_dr_j.x *MULTIPLIER,centru_dr_j.y *MULTIPLIER, centru_dr_s.x *MULTIPLIER, centru_dr_s.y *MULTIPLIER,
            centru_st_s.x *MULTIPLIER, centru_st_s.y *MULTIPLIER, color);

    //we use all the points we calculated to make 8 other squares by dividing the big square into 9 and not taking the
    //middle

    sierpinski(a, stanga_s, centru_st_s, sus_st, step-1, fp);
    sierpinski(stanga_s, stanga_j, centru_st_j, centru_st_s, step-1, fp);
    sierpinski(stanga_j, b, jos_st, centru_st_j, step-1, fp);
    sierpinski(centru_st_j, jos_st, jos_dr, centru_dr_j, step-1, fp);
    sierpinski(centru_dr_j, jos_dr, c, dreapta_j, step-1, fp);
    sierpinski(centru_dr_s, centru_dr_j, dreapta_j, dreapta_s, step-1, fp);
    sierpinski(sus_dr, centru_dr_s, dreapta_s, d, step-1, fp);
    sierpinski(sus_st, centru_st_s, centru_dr_s, sus_dr, step-1, fp);

}

int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        printf("Please use a command line argument to specify the number of iterations.");
        exit(1);
    }

    //we use this points to create a small square that we are going to scale with MULTIPLIER
    point a = {1,1};
    point b = {2,1};
    point c = {2,2};
    point d = {1,2};

    unsigned long ITRS = strtoul(argv[1], NULL, 0);

    FILE *fp = fopen ("sierpinski.svg", "w");

    fprintf(fp,"<svg style=\"background: cyan\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    sierpinski(a,b,c,d, ITRS, fp);

    fprintf(fp,"</svg>\n");

    fclose (fp);

    return 0;
}
