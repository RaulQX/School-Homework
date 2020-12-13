#include <stdio.h>
#include <stdlib.h>

#define MONEY 5

int coinz[] = {1, 2, 5};

int cchange(int coin_nums, int n, int* solved)
{
    solved[0] = 1;

    for(int i=0; i<coin_nums; i++)
        for(int j=coinz[i]; j <= n; j++)
            solved[j] += solved[j-coinz[i]];

    return solved[n];
}

int main()
{
    int coin_nums = sizeof(coinz)/sizeof(coinz[0]);
    int *solved = NULL;
    solved = calloc(MONEY + 1, sizeof(int));
    printf("There are %d ways to make change\n", cchange(coin_nums, MONEY, solved));

    free(solved);

    return 0;
}
