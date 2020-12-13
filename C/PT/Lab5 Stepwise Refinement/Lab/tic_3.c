#include <stdio.h>
#include <stdlib.h>
#define bd_dim 3	

unsigned board[3][3];

void print_hello()
{
	printf("Welcome to the game!\n");
}


void print_board()
{
	for (int i=0; i < bd_dim; i++)
	{	
		for (int j=0; j < bd_dim; j++)
		{
			if (board[i][j]==0)
				printf("[ ]");
			if (board[i][j]==1)
				printf("[X]");
			if (board[i][j]==2)
				printf("[0]");
		}
		printf("\n");
	}
}

unsigned player1()
{
	printf("here's the player playing\n");
	return 0;
}

unsigned computer()
{
	printf("here's the computer playing\n");
	return 0;
}

void test_board()
{
	for (int i=0; i<bd_dim; i++)
		for (int j=0; j<bd_dim; j++)
			board[i][j]=rand()%2+1;
	printf("here's a dummy board to see how it could look like.\n");
	print_board();
}

int main ()
{
	unsigned iswon=0;

	print_hello();

	print_board();

	while (!iswon)
	{
		iswon=player1();
		print_board();
		iswon=computer();
		print_board();
		iswon=1;
	}

	test_board();

	return 0;
}