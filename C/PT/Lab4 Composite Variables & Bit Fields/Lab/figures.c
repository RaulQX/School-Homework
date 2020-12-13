#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x,y;
}coords;

typedef struct {
	float radius;
	coords centre;
}circle_t;

typedef struct {
	coords a,b,c;
}triangle_t;

typedef struct {
	coords a,d;
}rectangle_t;

typedef enum
{	circ, tri, rect   }fig;

typedef union
{
	circle_t circle;
	triangle_t triangle;
	rectangle_t rectangle;

}figure_choose;

typedef struct
{
	unsigned int flag : 2;
	figure_choose figure;

}obiect;

void menu ()
{
	int n;
	int cont_circ=0;
	int cont_tri=0;
	int cont_rect=0;
	unsigned key;

	printf("Please introduce the number of figures: \n");
	scanf("%d",&n);

	obiect figures[n];

	for (int i=0; i<n; i++)
	{
		printf("Are you introducing a circle, a triangle or a rectangle? [0,1,2]: ");
		scanf("%u", &key);
		switch (key)
		{
			case circ:
				figures[i].flag=circ;

				printf("Please introduce the radius: ");
				scanf("%f", &figures[i].figure.circle.radius);
				if (figures[i].figure.circle.radius < 0)
				{
					printf("Not a valid circle!\n");
					exit(1);
				}
				printf("Please introduce the centre coordinates [x y]: ");
				scanf("%f %f", &figures[i].figure.circle.centre.x, &figures[i].figure.circle.centre.y);

				break;

			case tri:
				figures[i].flag=tri;

				printf("Please introduce the coordinates of A [x y]: ");
				scanf("%f %f", &figures[i].figure.triangle.a.x, &figures[i].figure.triangle.a.y);
				printf("Please introduce the coordinates of B [x y]: ");
				scanf("%f %f", &figures[i].figure.triangle.b.x, &figures[i].figure.triangle.b.y);
				printf("Please introduce the coordinates of C [x y]: ");
				scanf("%f %f", &figures[i].figure.triangle.c.x, &figures[i].figure.triangle.c.y);

				break;

			case rect:
				figures[i].flag=rect;

				printf("Please introduce the coordinates of A [x y]: ");
				scanf("%f %f", &figures[i].figure.rectangle.a.x, &figures[i].figure.rectangle.a.y);
				printf("Please introduce the coordinates of D [x y]: ");
				scanf("%f %f", &figures[i].figure.rectangle.d.x, &figures[i].figure.rectangle.d.y);

				break;

			default:
				printf("Value is not good! Please introduce it again! [0 1 2]\n");
				i--;

				break;
		}
	}
	
	for (int i=0; i<n; i++)
	{
		if (figures[i].flag==circ)
		{
			cont_circ++;
			printf("Circle #%d has the centre at (%f, %f) and has radius %f\n", cont_circ, figures[i].figure.circle.centre.x,
				figures[i].figure.circle.centre.y, figures[i].figure.circle.radius);
		}
		if (figures[i].flag==tri)
		{
			cont_tri++;
			printf("Triangle #%d has the point A at (%f, %f), point B at (%f, %f) and point C at (%f, %f)\n", cont_tri, figures[i].figure.triangle.a.x,
				figures[i].figure.triangle.a.y, figures[i].figure.triangle.b.x, figures[i].figure.triangle.b.y, figures[i].figure.triangle.c.x,
				figures[i].figure.triangle.c.y);
		}
		if (figures[i].flag==rect)
		{
			cont_rect++;
			printf("Rectangle #%d has the point A at (%f, %f), point D at (%f, %f)\n", cont_rect, figures[i].figure.rectangle.a.x, figures[i].figure.rectangle.a.y,
				figures[i].figure.rectangle.d.x, figures[i].figure.rectangle.d.y);
		}
	}
}


int main ()
{
	menu();

	return 0;
}
