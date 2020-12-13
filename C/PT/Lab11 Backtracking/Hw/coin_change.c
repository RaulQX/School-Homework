#include <stdio.h>
#include <string.h>

int condition (int current_currency, int sum)
{
    if (current_currency <= sum)
        return 1;
    return 0;
}

void print_sol(int *solution, int k)
{
    for (int i=0; i<k; i++)
        printf("%d ", solution[i]);

    printf("\n");

}

void backtrack(int *coins, int total_coins, int current_currency, int sum, int *solution, int contor_sol)
{
    for (int i=0; i<total_coins; i++)
    {
        solution[contor_sol] = coins[i];
        current_currency += solution[contor_sol++];

        if (condition(current_currency, sum))
        {
            if (current_currency == sum)
                print_sol(solution,contor_sol);

            else
                backtrack(coins, total_coins, current_currency, sum, solution, contor_sol);
        }

        contor_sol--;
        current_currency -= solution[contor_sol];
        solution[contor_sol] = 0;
    }
}

int main()
{
    int sum;
    printf("Please introduce the sum you would like to split: ");
    scanf("%d", &sum);

    int coins[]= {2, 3, 5, 7};
    int total_coins = sizeof(coins)/sizeof(coins[0]);

    int total_sol_space = sum/coins[0] + 1;
    int solution[total_sol_space];

    memset(solution, 0, total_sol_space*sizeof(int));

    backtrack(coins, total_coins, 0, sum, solution, 0);

    return 0;
}
