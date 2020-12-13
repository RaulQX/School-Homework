#include <stdio.h>
#include <stdlib.h>
#define TOTAL_COINS 4
//1 5 10 20

void fill(unsigned *coinstash)
{
	coinstash[0]=20;
	coinstash[1]=10;
	coinstash[2]=5;
	coinstash[3]=1;
}

void print_coins_used(unsigned *coinstash)
{
	printf("Coins of 20: %u\n",coinstash[0]);
	printf("Coins of 10: %u\n",coinstash[1]);
	printf("Coins of  5: %u\n",coinstash[2]);
	printf("Coins of  1: %u\n",coinstash[3]);
}

unsigned greedy(unsigned value, unsigned *coins, unsigned *available_coins)
{
	unsigned count_coins=0;

	for (int i=0; i<TOTAL_COINS; i++)
		while(value >= available_coins[i])
		{
			coins[i]++;
			count_coins++;
			value -= available_coins[i];
		}

	return count_coins;
}

int main ()
{
	unsigned value;
	unsigned coins[TOTAL_COINS]={0};
	unsigned available_coins[TOTAL_COINS];
	unsigned tot_coins;

	printf("Please introduce the value: ");
	scanf("%u", &value);

	fill(available_coins);

	tot_coins=greedy(value, coins, available_coins);

	printf("Minimum number of coins: %u\n", tot_coins);
	print_coins_used(coins);

	return 0;
}
