#include <stdio.h>
#include <stdlib.h>

long int *fibo_nums = NULL;
long int maxi;
long int contor;

void allocate_fibo_space(long n)
{
    fibo_nums = (long int*) realloc (fibo_nums, sizeof(long int)*(n+1));

    for (long int i=maxi; i<n; i++)
        fibo_nums[i] = -1;
}

void print_fibo ()
{
    for (long int i=0; i < maxi; i++)
        printf("%ld ", fibo_nums[i]);

    printf("\n");
}

int make_fibonacci(long int n) //n is the n-th term
{
    if (n==0 || n==1)
    {
        printf("\nWe are re-using fibo_nums[%ld] (%ld)\n", n, fibo_nums[n]);

        return fibo_nums[n];
    }
    else
    {
        if (n >= maxi)
        {
            printf("\nWe are re-using fibo_nums[%ld] (%ld) and fibo_nums[%ld] (%ld)\n", maxi-1, fibo_nums[maxi-1],
                   maxi-2, fibo_nums[maxi-2]);

            allocate_fibo_space(n);

            for (int i = maxi; i < n; i++)
            {
                if (fibo_nums[i] == -1)
                    fibo_nums[i] = fibo_nums[i-1] + fibo_nums[i-2];
            }

            maxi = n;
        }

        else
            printf("\nWe are re-using fibo_nums[%ld] (%ld)\n", n-1, fibo_nums[n-1]);

        return fibo_nums[n-1];
    }

}

long int fibo_recursiv (long int n)
{
    contor++;

    if (n==0)
        return 0;
    else if (n==1)
        return 1;

    else
        return fibo_recursiv(n-2) + fibo_recursiv(n-1);
}

void apel_fibo_rec(int n)
{
    contor=0;
    printf("Fibo recursiv: %ld\n",fibo_recursiv(n));
    printf("Contor recursiv: %ld\n",contor);
}

void apel_fibo_dinamic(int n)
{
    printf("Fibo dinamic: %ld \n",make_fibonacci(n));
    printf("Max terms calculated: %ld\n",maxi);
}
int main()
{
    allocate_fibo_space(2);

    fibo_nums[0]=0;
    fibo_nums[1]=1;
    maxi = 2;


    apel_fibo_dinamic(4);
    printf("\n");
    apel_fibo_rec(3);

    apel_fibo_dinamic(12);
    printf("\n");
    apel_fibo_rec(11);

    apel_fibo_dinamic(5);
    printf("\n");
    apel_fibo_rec(4);


    apel_fibo_dinamic(24);
    printf("\n");
    apel_fibo_rec(23);

    apel_fibo_dinamic(4);
    printf("\n");
    apel_fibo_rec(3);

    printf("\nSir fibo dinamic:\n");
    print_fibo();

    free(fibo_nums);
    return 0;
}
