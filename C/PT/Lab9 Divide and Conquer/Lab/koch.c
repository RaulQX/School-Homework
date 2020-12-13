#include <stdio.h>
#include <stdlib.h>
#define iterations 4

unsigned line_counter=0;

typedef struct point
{
    double x;
    double y;
}point;

typedef struct lines
{
    point p1;
    point p2;
}lines;

lines liniute[1200000];

point calculate_c(point a, point b)
{
    point c;
    point rotated;

    c.x = b.x - a.x;
    c.y = b.y - a.y;

    rotated.x = (0.5 * c.x - 0.866 * c.y) + a.x;
    rotated.y = (0.866 * c.x + 0.5 * c.y) + a.y;

    return rotated;
}

int n=300;
int m=400;

void make_svg()
{
    
    for (int i=0; i<line_counter; i++)
    {
        printf("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", 
            liniute[i].p1.x*n+m,liniute[i].p1.y*n+m,liniute[i].p2.x*n+m,liniute[i].p2.y*n+m);
        
    }
}

void fractal(unsigned itrs, lines d1)
{
    if (itrs == 1)
    {
        make_svg();
        return;
    }


    point a,b,c,d,e;

    a=d1.p1;

    double dirx, diry;

    dirx=(d1.p2.x - d1.p1.x)/3.0;
    diry=(d1.p2.y - d1.p1.y)/3.0;


    b.x=d1.p1.x + dirx;
    b.y=d1.p1.y + diry;

    d.x=d1.p1.x + 2 * dirx;
    d.y=d1. p1. y + 2* diry;

    c=calculate_c(b,d);

    e=d1.p2;

    //printf("a: %lf %lf\nb: %lf %lf\nc: %lf %lf \nd: %lf %lf\ne: %lf %lf\n\n",a.x,a.y,b.x,b.y,c.x,c.y,d.x,d.y,e.x,e.y);

    lines new_ab, new_bc, new_cd, new_de;

    new_ab.p1=a;
    new_ab.p2=b;

    new_bc.p1=b;
    new_bc.p2=c;

    new_cd.p1=c;
    new_cd.p2=d;

    new_de.p1=d;
    new_de.p2=e;


    if (itrs==2)
    {
        liniute[line_counter++]=new_ab;
        liniute[line_counter++]=new_bc;
        liniute[line_counter++]=new_cd;
        liniute[line_counter++]=new_de;
    }


    fractal(itrs-1, new_ab);
    fractal (itrs-1, new_bc);
    fractal (itrs-1, new_cd);
    fractal(itrs-1, new_de);

}

void fractal_trig(unsigned itrs, lines ab, lines bc, lines ca)
{
    fractal(itrs, ab);
    fractal(itrs, bc);
    fractal(itrs, ca);
}

void koch(unsigned itrs)
{
    point a,b,c;
    lines ab,bc,ca;

    a.x=0;
    a.y=1;

    b.x=0.87;
    b.y=-0.5;

    c.x=-0.87;
    c.y=-0.5;

    ab.p1=a;
    ab.p2=b;

    bc.p1=b;
    bc.p2=c;

    ca.p1=c;
    ca.p2=a;

    switch(itrs)
    {
        case 0:
            printf("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",a.x*n+m,a.y*n+m,b.x*n+m,b.y*n+m);
            break;
        case 1:
            printf("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",a.x*n+m,a.y*n+m,b.x*n+m,b.y*n+m);
            printf("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",b.x*n+m,b.y*n+m,c.x*n+m,c.y*n+m);
            printf("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",c.x*n+m,c.y*n+m,a.x*n+m,a.y*n+m);
            printf("Points of the triangle are (%lf %lf) (%lf %lf) (%lf %lf)", a.x,a.y,b.x,b.y,c.x,c.y);
            break;
        default:
            fractal_trig(itrs, ab, bc, ca);
            break;

    }
}



int main ()
{

    printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

        koch(iterations);

    printf("</svg>\n");
    return 0;
}
