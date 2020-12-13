#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned insert_counter =0;
unsigned merge_counter =0;

void merge (int* v, int left, int middle, int right)
{
	int i,j,k;

	int n1=middle-left+1;
	int n2=right-middle;

	int lv[n1],rv[n2];

	for (i = 0; i < n1; i++)
	{
		lv[i]=v[left+i];
	}
	for (i = 0; i < n2; i++)
	{
		rv[i]=v[middle+1+i];
	}

	i=0; j=0; k=left;

	while (i<n1 && j<n2)
	{
		if (lv[i]<rv[j])
		{
			v[k]=lv[i];
			k++;
			i++;
		}
		else
		{
			v[k]=rv[j];
			k++;
			j++;
		}
		merge_counter++;
	}

	while (i<n1)
	{
		v[k]=lv[i];
		k++;
		i++;
	}
	while (j<n2)
	{
		v[k]=rv[j];
		k++;
		j++;
	}

}

void merge_sort(int *v, int left, int right)
{
	if (left<right)
	{
		int middle = (left + right)/2;
		merge_sort(v, left, middle);
		merge_sort(v, middle+1, right);

		merge(v,left,middle,right);
	}
}

void insertion_sort (int *v, int n)
{
	int i, j, aux;
	for(i=1; i<n; i++)
	{
		aux=v[i];
		for (j=i-1; j>=0 && v[j]>aux; j--)
		{
			v[j+1]=v[j];
			insert_counter++;
		}
		v[j+1]=aux;
	}
}

void populate_vect(int *v, int n)
{
	srand(time(0));

	for (int i=0; i<n; i++)
		v[i]=rand()%1000;
}

void copy_vector(int *v_to, int *v_from, int n)
{
	for (int i=0; i<n; i++)
		v_to[i]=v_from[i];
}

void print_vect(int *v, int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", v[i]);
	putchar('\n');
}

void comp_merg_ins()
{
	int n;
	printf("Introduce vector dimension: ");
	scanf("%d",&n);
	
	int v[n],vIns[n],vMerge[n];

	populate_vect(v,n);
	copy_vector(vIns, v, n);
	copy_vector(vMerge, v, n);

	printf("Vector before sorting:\n");
	print_vect(v,n);

	printf("\nVector after sorting with insertion sort:\n");
	insertion_sort(vIns,n);
	print_vect(vIns,n);
	printf("Total number of swaps: %d\n", insert_counter);

	printf("\nVector after sorting with merge sort:\n");
	merge_sort(vMerge,0,n-1);
	print_vect(vMerge,n);
	printf("Total number of swaps: %d\n", merge_counter);
}

int main ()
{
	comp_merg_ins();
	
	return 0;
}