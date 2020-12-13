#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge (unsigned* v, int left, int middle, int right)
{
	int i,j,k;

	int n1=middle-left+1;
	int n2=right-middle;

	int lv[n1],rv[n2];

	for (i = 0; i < n1; i++)
		lv[i]=v[left+i];

	for (i = 0; i < n2; i++)
		rv[i]=v[middle+1+i];

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

void merge_sort(unsigned *v, int left, int right)
{
	if (left<right)
	{
		int middle = (left + right)/2;

		merge_sort(v, left, middle);
		merge_sort(v, middle+1, right);

		merge(v,left,middle,right);
	}
}

int linear_search(unsigned *v, int x, int n)
{
	for (int i=0; i<n; i++)
		if (x==v[i])
			return i+1;

	return -1;
}

int bsrch_nonrec(unsigned *v, int left, int right, int num, int *p)
{
	int middle;
	*p=1;

	while (left<=right)
	{
		middle=(left+right)/2;

		if (v[middle]==num)
			return middle;

		if (num>v[middle])
		{
			left=middle+1;
			(*p)++;
		}
		else
		{
			right=middle-1;
			(*p)++;
		}
	}

	return -1;
}

int pow2(int n)
{
	int a=1;

	for (int i=0; i<n; i++)
		a=a*2;
	
	return a;
}

void populate_vect(unsigned *v, int n, int mod)
{
	for (int i=0; i<n; i++)
		v[i]=rand()%mod;
}

void comp(int size, int x, int mod)
{
	int n=size;
	size=pow2(size);

	unsigned v[size];
	int lin_srch_counter;
	int bsrch_counter;
	int *p = &bsrch_counter;
	int found;

	populate_vect(v,size,mod);

	lin_srch_counter=linear_search(v,x,size);

	merge_sort(v,0,size-1);
	found=bsrch_nonrec(v, 0, size-1, x, p);

	if (lin_srch_counter == -1)
	{
		printf("For N=%d, 2^%d (%d), %d was not found, we try again by re-populating the vector.\n",n,n, size, x);
		comp(n,x,mod);
	}
	else
	{
		printf("\nFor a vector of size 2^%d (%d), searching for the number %d with all the elements being smaller than %d:\n",n,size,x,mod);
		printf("Linear search took %d tries. (position %d)\n", lin_srch_counter, lin_srch_counter-1);
		printf("Binary search took %d tries, found at v[%d].\n\n", bsrch_counter, found);
	}
}

int main ()
{
	srand(time(0));
	int a;
	int mod;
	int N=17;
	for (int i=10; i<=N; i++)
	{	
		mod=pow2(i);
		a=rand()%mod;
		comp(i, a, mod);
	}
	
	return 0;
}