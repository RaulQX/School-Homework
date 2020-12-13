#include <stdio.h>
#include <stdlib.h>

void print_hello()
{
	printf("Welcome to the game!\n");
}


void print_board()
{
	printf("printed board\n");
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

	return 0;
}