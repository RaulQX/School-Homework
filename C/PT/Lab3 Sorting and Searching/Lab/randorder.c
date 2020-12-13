#include <stdio.h>
#include <stdlib.h>

//n1=[l...m] = m-l+1;
//n2=[m+1...r] = r-m-1+1 = r-m

void merge (int* v, int left, int middle, int right)
{

	int i, j, k;
	int n1= middle - left + 1;
	int n2= right - middle;

	int leftvect[n1], rightvect[n2];

	for (i=0; i<n1; i++)
		leftvect[i] = v[left+i];
	for (i=0; i<n2; i++)
		rightvect[i] = v[i+middle+1];

	i=0;
	j=0;
	k=left;

	while (i<n1 && j<n2)
	{
		if(leftvect[i] <= rightvect[j])
		{
			v[k] = leftvect[i];
			i++;
		}
		else
		{
			v[k] = rightvect[j];
			j++;
		}
		k++;
	}

	while (i<n1)
	{
		v[k] = leftvect[i];
		i++;
		k++;
	}

	while (j<n2)
	{
		v[k] = rightvect[j];
		j++;
		k++;
	}
}

void mergesort(int *v, int l, int r)
{
	if (l<r)
	{
		int m=(l+r)/2;

		mergesort(v, l, m);
		mergesort(v, m+1, r);

		merge (v, l, m, r);
	}
}

int main ()
{
	unsigned n;

	printf("Please introduce the number of elements.\n");
	if(scanf("%u", &n)!=1)
	{
		printf("Please introduce an unsigned number of elements.\n");
		exit(1);
	}

	int v[n];

	for (int i=0; i<n; i++)
			v[i]=rand()%100;

	printf("Vector before sorting:\n");

	for (int i=0; i<n; i++)
		printf("%d ", v[i]);
	putchar('\n');

	mergesort(v, 0, n-1);

	printf("Vector after sorting:\n");

	for (int i=0; i<n; i++)
		printf("%d ", v[i]);

	putchar('\n');


	return 0;
}