#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 5

struct gshape
{
    int type;
    int ID;
    union
    {
        struct
        {
            float radius;
            float x,y;

        } circle;

        struct
        {
            float x1,y1;
            float x2,y2;
            float x3,y3;

        } triangle;

        struct
        {
            float x1,y1;
            float x4,y4;

        } rectangle;

    } gshape;

    double area;

    void (*read_gshape) (struct gshape *gs);
    void (*write_gshape) (struct gshape *gs);

};

void read_circle (struct gshape *gs)
{
    printf("Radius: ");
    scanf("%f", &(gs->gshape.circle.radius));

    printf("Center coords: [X Y]: ");
    scanf ("%f %f", &(gs->gshape.circle.x), &(gs -> gshape.circle.y));

    gs->area = 3.14 * gs->gshape.circle.radius * gs->gshape.circle.radius;
}

void write_circle (struct gshape *gs)
{
    printf("Printing circle with ID: %d\n", gs->ID);

    printf("Radius: %f\n", gs->gshape.circle.radius);
    printf("Center: %f %f\n", gs->gshape.circle.x,gs->gshape.circle.y);
    printf("Area: %lf\n", gs->area);
}

void read_triangle (struct gshape *gs)
{
    printf("[x1 y1]: ");
    scanf("%f %f", &(gs->gshape.triangle.x1),&(gs->gshape.triangle.y1));

    printf("[x2 y2]: ");
    scanf("%f %f", &(gs->gshape.triangle.x2),&(gs->gshape.triangle.y2));

    printf("[x3 y3]: ");
    scanf("%f %f", &(gs->gshape.triangle.x3),&(gs->gshape.triangle.y3));

    //area: |Ax(By - Cy) + Bx(Cy - Ay) + Cx(Ay - By)|/2.

    gs->area = fabs(( gs->gshape.triangle.x1 * (gs->gshape.triangle.y2 - gs->gshape.triangle.y3) +
                      gs->gshape.triangle.x2 * (gs->gshape.triangle.y3 - gs->gshape.triangle.y1) +
                      gs->gshape.triangle.x3 * (gs->gshape.triangle.y1 - gs->gshape.triangle.y2)) /2.0);
}

void write_triangle (struct gshape *gs)
{
    printf("Printing triangle with ID :%d\n", gs->ID);

    printf("The triangle has the points\n a(%f %f) b(%f %f) c(%f %f)\n",
           (gs->gshape.triangle.x1), (gs->gshape.triangle.y1), (gs->gshape.triangle.x2),
           (gs->gshape.triangle.y2), (gs->gshape.triangle.x3), (gs->gshape.triangle.y3));

    printf("Area: %lf\n", gs->area);

}

void read_rectangle (struct gshape *gs)
{
    double ab,bc;

    printf("[x1 y1]: ");
    scanf("%f %f", &(gs->gshape.rectangle.x1),&(gs->gshape.rectangle.y1));

    printf("[x4 y4]: ");
    scanf("%f %f", &(gs->gshape.rectangle.x4),&(gs->gshape.rectangle.y4));

    ab = sqrt((gs->gshape.rectangle.y1 - gs->gshape.rectangle.y4)*(gs->gshape.rectangle.y1 - gs->gshape.rectangle.y4));
    bc = sqrt((gs->gshape.rectangle.x1 - gs->gshape.rectangle.x4)*(gs->gshape.rectangle.x1 - gs->gshape.rectangle.x4));

    gs->area = ab*bc;
}

void write_rectangle (struct gshape *gs)
{
    printf("Printing rectangle with ID :%d\n", gs->ID);

    printf("The rectangle has the points a(%f %f) b(%f %f) c(%f %f) d(%f %f)\n",
           (gs->gshape.rectangle.x1), (gs->gshape.rectangle.y1), (gs->gshape.rectangle.x1),
           (gs->gshape.rectangle.y4), (gs->gshape.rectangle.x4), (gs->gshape.rectangle.y4),
           (gs->gshape.rectangle.x4), (gs->gshape.rectangle.y1));

    printf("Area: %lf\n", gs->area);
}

int main()
{
    struct gshape gs[N];

    int type;
    int count_circles=0;
    int count_rects=0;
    int count_trigs=0;

    char *name[]= {"circle", "triangle", "rectangle"};

    printf("Initializing the geometric shapes collection\n");

    for (int i=0; i<N; i++)
    {
        do
        {
            printf("Shape ID: %d\n",i);

            printf("What shape is it? (0 - circle, 1 - triangle, 2 - rectangle): ");
            scanf("%d", &type);

            gs[i].type=type;
            gs[i].ID=i;

            switch (gs[i].type)
            {
                case 0:
                    gs[i].read_gshape = &read_circle;
                    gs[i].write_gshape = &write_circle;
                    count_circles++;
                    break;

                case 1:
                    gs[i].read_gshape = &read_triangle;
                    gs[i].write_gshape = &write_triangle;
                    count_trigs++;
                    break;

                case 2:
                    gs[i].read_gshape = &read_rectangle;
                    gs[i].write_gshape = &write_rectangle;
                    count_rects++;
                    break;

                default:
                    printf("Please introduce numbers from 0 to 2\n");
                    exit(1);
            }
        }while ((gs[i].type !=0) && (gs[i].type !=1) && (gs[i].type !=2));
    }

    printf("\n\n");

    for (int i=0; i<N; i++)
    {
        printf("Reading %s with ID %d\n", name[gs[i].type], i);
        gs[i].read_gshape(&gs[i]);
    }

    printf("\n\n");

    if (count_rects != 0)
    {
        printf("Printing all rectangles: \n");

        for (int i=0; i<N; i++)
            if (gs[i].type == 2)
                gs[i].write_gshape(&gs[i]);
    }
    else
        printf("No rectangles in the database.\n");

    return 0;
}
