#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define bd_dim 3	
#define draw 10

unsigned board[3][3];
unsigned chosen[9];
unsigned total_moves=0;

void print_hello()
{
	printf("Welcome to the game! \n");
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
	putchar('\n');
}

unsigned win_check(int n)
{
	total_moves++;

	if (board[0][0]==n && board[0][1]==n && board[0][2]==n)
		return 1;
	if (board[1][0]==n && board[1][1]==n && board[1][2]==n)
		return 1;
	if (board[2][0]==n && board[2][1]==n && board[2][2]==n)
		return 1;

	if (board[0][0]==n && board[1][0]==n && board[2][0]==n)
		return 1;
	if (board[0][1]==n && board[1][1]==n && board[2][1]==n)
		return 1;
	if (board[0][2]==n && board[1][2]==n && board[2][2]==n)
		return 1;

	if (board[0][0]==n && board[1][1]==n && board[2][2]==n)
		return 1;
	if (board[0][2]==n && board[1][1]==n && board[2][0]==n)
		return 1;

	return 0;
}

unsigned player1()
{	
	unsigned lin,col;
	unsigned pwin=0;

	printf("Player's turn\nPlease introduce the coordinates where you would like to place X. [x y]\n");
	print_board();

	scanf ("%d %d", &lin, &col);

	if (board[lin][col] != 0 || lin>2 || col>2)
	{
		printf("Not a good choice!\n");
		player1();
	}
	else
	{
		board[lin][col] = 1;
		chosen[3*lin+col]++;
		pwin=win_check(1);
	}

	return pwin;
}

unsigned computer()
{

	unsigned rand_move, lin, col;
	unsigned is_ok=0;
	unsigned comp_win=0;
	
	printf("Computer's turn.\n");

	while(!is_ok)
	{
		rand_move=rand()%9;
		if (chosen[rand_move]==0)
		{
			is_ok=1;
			chosen[rand_move]++;
			lin=rand_move/3;
			col=rand_move%3;
			board[lin][col]=2;
		}
	}

	comp_win=win_check(2);

	return comp_win;
}

void clear ()
{
	for (int i=0 ; i<9; i++)
		for (int j=0; j<9; j++)
			board[i][j]=0;
	total_moves=0;
	for (int i=0; i<9; i++)
		chosen[i]=0;

}

void game()
{
	unsigned iswon=0;
	
	while (1)
	{
		if (total_moves < 9)
		{	
			iswon=player1();
			print_board();
			if(iswon==1)
			{
				printf("Player wins\n");
				return;
			}
		}
		if (total_moves < 9)
		{
			iswon=computer();
			print_board();
			if(iswon==1)
			{
				printf("Computer wins\n");
				return;
			}
		}
		else 
		{
			printf("Draw\n");
			return;
		}
	}

}

void menu()
{
	int key;
	print_hello();
	while (1)
	{	
		printf("What would you like to do?\n");
		printf("Start a new game [1].\n");
		printf("Exit [2]\n");
		scanf("%d",&key);
		switch (key)
		{
			case 1:
				clear();
				game();
				break;
			case 2:
				return;
			default:
				printf("Wrong number!\n");
				break;
		}
	}
}

int main ()
{
	srand(time(0));
	menu();
	
	return 0;
}