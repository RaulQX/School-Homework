#include <stdio.h>
#include <stdlib.h>
#define N 3
#define X 70
#define Y 400

//N is number of discs
//X and Y are scalars (don't change)


/*
######################################################
Using Google Chrome on 1920x1080, zoom 25% looks great
(Tested on windows 10 as I see in my Ubuntu only the
pictogram is made okay).
######################################################
*/

typedef struct discs
{
	unsigned dim;
	unsigned pos;
}disk;

void make_disks (disk *discs)
{
	for (int i=1; i<=N; i++)
	{
		discs[i].dim=i;
		discs[i].pos=1;
	}
}

int i=0;

void make_table(unsigned x, unsigned y, disk *v)
{
    int k=0;
    int remember_the_i;

 	int just_above1=50;
    int just_above2=50;
    int just_above3=50;

    i++;
    remember_the_i=i;

    while (i>0)
    {
        i=i-6;
        if (i>0)
            k++;
    }
    
    i=remember_the_i;
    x+=(1000*k);

    if (i%6!=0)
    	y=y*(i%6);
    
    else y=y*6;

	printf("<rect x=\"%u\" y=\"%u\" width=\"30\" height=\"270\" fill=\"yellow\" stroke-width=\"2\" stroke=\"black\" />\n",x+5, y-200);
	printf("<rect x=\"%u\" y=\"%u\" width=\"30\" height=\"270\" fill=\"yellow\" stroke-width=\"2\" stroke=\"black\" />\n",x+325, y-200);
	printf("<rect x=\"%u\" y=\"%u\" width=\"30\" height=\"270\" fill=\"yellow\" stroke-width=\"2\" stroke=\"black\" />\n",x+645, y-200);
	printf("<rect x=\"%u\" y=\"%u\" width=\"700\" height=\"90\" fill=\"yellow\" stroke-width=\"4\" stroke=\"black\" />\n",x, y);

	for (int j=N; j>=1; j--)
	{
		if (v[j].pos==1)
		{
			printf("<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"50\" fill=\"red\" stroke-width=\"2\" stroke=\"black\" />\n",x-10*j, y-just_above1, v[j].dim*30+50);
			just_above1+=50;
		}

		else if (v[j].pos==2)
		{
			printf("<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"50\" fill=\"red\" stroke-width=\"2\" stroke=\"black\" />\n",x+310-10*j, y-just_above2, v[j].dim*30+50);
			just_above2+=50;
		}

		else
		{
			printf("<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"50\" fill=\"red\" stroke-width=\"2\" stroke=\"black\" />\n",x+620-10*j, y-just_above3, v[j].dim*30+50);
			just_above3+=50;
		}
	}
}

void md(unsigned n, char from, char to, char aux, disk *v)
{
	if (n==1)
	{
		v[1].pos=to-'0';
		make_table(X,Y,v);
	}
	else
	{
		md(n-1, from, aux, to, v);

		v[n].pos=to-'0';
		make_table(X,Y,v);

		md(n-1, aux, to, from, v);
	}
}

void svg(disk *v, unsigned n)
{
	// this function was made to accomodate myself with svg and to help, is not used in the program
	unsigned y_axis=200;
	unsigned x_axis=50;
	int k=0;
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	printf("<svg height =\"5000\">\n");

	for (int i=0; i<31; i++)
	{
		k++;

		if (i%6==0 && i!=0)
		{
			x_axis=x_axis+800;
			k=1;
		}

		make_table(x_axis,2*k*y_axis,v);
	}

	printf("</svg>\n");
}


int main ()
{
	disk v[N+1];
	make_disks(v);

	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
		
		make_table(X,Y,v);
		md(N, '1', '3', '2', v);

	printf("</svg>\n");
	return 0;
}
