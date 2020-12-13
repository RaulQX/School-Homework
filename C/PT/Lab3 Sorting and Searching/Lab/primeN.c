#include <stdio.h>
#include <stdlib.h>

int bsrch(unsigned *v, int left, int right, int num)
{
	int middle;
	if (left<=right)
	{
		middle=(left+right)/2;

		if (v[middle] == num)
			return middle;

		else if (v[middle] > num)
			return bsrch(v, left, middle -1, num);

		else return bsrch (v, middle + 1, right, num);
	}

	return -1;
}


int testpr(int x)
{
	int sw=1;

	if (x>=2)
	{
		for (int i=2; i<x; i++)
			if (x%i==0)
				sw=0;
	}
	else sw=0;

	return sw;
}

void populate_vect(unsigned *v, int n)
{
	int i=0;
	int prim;
	unsigned k=1;
	while (i<n)
	{
		k++;
		prim=testpr(k);
		if (prim==1)
			v[i++]=k;
	}
}

void prime()
{
	int i=0;
	unsigned n;
	int x;

	printf("How many prime numbers would you like?: ");
	scanf("%u", &n);

	unsigned v[n];
	populate_vect(v,n);

	printf("The vector of prime numbers is: \n");
	for (i=0; i<n; i++)
		printf("%u ", v[i]);
	putchar ('\n');

	printf("Please introduce your number: ");
	scanf("%u", &x);

	if (testpr(x)==0)
	{
		printf("Your number is not prime.\n");
		exit(1);
	}
	else
	{
		int exists=bsrch(v,0,n-1,x);
		if (exists!=-1)
			printf("Your number exists inside the array on position: %d\n", exists);
		else
			printf("Your number doesn't exist in the array, please extend it.\n");
	}

}

int main ()
{
	prime();

	return 0;
}