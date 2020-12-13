#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10
#define MAX 20

void populate_array(int *v, int n, int maxim)
{
	for (int i=0; i<n; i++)
		v[i]=rand()%(maxim+1);

}

void print_array(int *v, int n)
{
	for (int i=0; i<n; i++)
		printf("%d ", v[i]);

	printf("\n");
}

unsigned contor_min_greed=0;
unsigned contor_max_greed=0;

void greedy(int *array, int n, int *min_greed, int*max_greed)
{
	for (int i=1; i<n-1; i++)
	{
		if (array[i]<array[i-1] && array[i]<array[i+1])
			min_greed[contor_min_greed++]=array[i];

		if (array[i]>array[i-1] && array[i]>array[i+1])
			max_greed[contor_max_greed++]=array[i];
	}
}


int main ()
{
	srand(time(0));

	int array [MAX_ELEMENTS];

	int min_greed[MAX_ELEMENTS],max_greed[MAX_ELEMENTS];

	populate_array(array, MAX_ELEMENTS,	 MAX);
	unsigned elems=sizeof(array)/sizeof(array[0]);
	print_array(array, elems);

	greedy(array, elems, min_greed, max_greed);

	print_array(min_greed, contor_min_greed);
	print_array(max_greed, contor_max_greed);

	return 0;
}