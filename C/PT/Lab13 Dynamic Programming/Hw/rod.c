#include <stdio.h>
#include <string.h>

typedef struct rod
{
	unsigned lenght[100];
	unsigned price[100];
}rod;

int calc_best_price(rod rodo, int n)
{
    int maximul=0;
    int valori[8];
	memset(valori, 0, sizeof(int)*n);

	for (int i=0; i<n; i++)
	{
		valori[i] = rodo.price[i];      //First we place the rod as one piece

		for (int k=i-1; k>0; k--)       //Then we compute here the best options that we found for the smaller pieces
			if (valori[i] < rodo.price[k] + valori[i-k-1])
				valori[i] = rodo.price[k] + valori[i-k-1];

		if (valori[i] > maximul)    //Here we remember the best price
			maximul = valori[i];
	}

	return maximul;
}


int main ()
{
	int n=8;  //Number of ways to cut the rod
	rod rodo ={{1, 2, 3, 4, 5, 6, 7, 8}, {1, 5, 8, 9, 10, 17, 17, 20}};

	printf("Most advantageous price for the rod is: %d\n", calc_best_price(rodo,n));

	return 0;
}
