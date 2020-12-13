#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void print_board(unsigned board[6][3][3], unsigned center)
{
	int i,j,k;
	for (j=0; j<3; j++)
	{
		printf("	   ");
		for (k=0; k<3; k++)
		{
			if (board[0][j][k]==0)
	            printf("[ ]");
        	if (board[0][j][k]==1)
            	printf("[X]");
       		if (board[0][j][k]==2)
            	printf("[0]");
		}
		printf("\n");
	}
	int count=0;
	printf("\n ");
	for (j=0; j<3; j++)
		for (i=1; i<=3; i++)
			for (k=0; k<3; k++)
			{
				if (board[i][j][k]==0)
               		printf("[ ]");
            	else if (board[i][j][k]==1)
                	printf("[X]");
           		else if (board[i][j][k]==2)
                	printf("[0]");
				if ((++count)%9==0)
					putchar('\n');
				if (count%3==0)
					putchar(' ');
			}
	putchar('\n');
	for (i=4; i<=6; i++)
	{	
		for (j=0; j<3; j++)
		{
			printf("	   ");
			for (k=0; k<3; k++)
			{
				if (board[0][j][k]==0)
		            printf("[ ]");
	        	if (board[0][j][k]==1)
	            	printf("[X]");
	       		if (board[0][j][k]==2)
	            	printf("[0]");
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("Cube center: ");
		if (center==0)
			printf("[ ]\n");
		else if (center==1)
			printf("[X]\n");
		else printf("[0]\n");
	putchar('\n');
}

void board_ex()
{
	unsigned board_example[6][3][3];
	for (int i=0; i<6; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
				board_example[i][j][k]=rand()%3;
	print_board(board_example, (rand()%2)+1);
}

void print_hello ()
{
	printf("Welcome to 3d Tic Tac Toe\n");

}

void display_rules()
{
	printf("A cube has 6 faces, on each face there is a 3x3 board.\n");
	printf("This is an example: \n\n");
	board_ex();
	sleep(2.5);
	printf("Each layer is counted in the order that it appears (0,1,...5).\n");
	sleep(1);
	printf("In order to choose where to place X or 0, please use this format:\n");
	sleep(1);
	printf("[Layer number] [i] [j], where i and j are the coordinates in a 3x3 matrix (starting from 0)\n");
	sleep(1);
	printf("If you wish to choose the center of the cube, please insert only '1'.\n");
	sleep(1);
	printf("Game is played with normal rules of Tic Tac Toe on every surface with the addition of the element in the cube-center\n");
	sleep(1);
	printf("You also win if you have corner, cube-center, opposite corner\n\n");
}

void game ()
{
	printf("here we play the game.\n");
}

void menu()
{
	int key;
	
	while (1)
	{
		printf("What would you like to do?\n");
		printf("Read the rules [0]\n");
		printf("Start a new game [1]\n");
		printf("Exit [2]\n");

		scanf("%d",&key);
	    switch (key)
	    {
	    case 0:
	        display_rules();
	        break;
	    case 1:
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

unsigned check_win ()
{
	printf("Here we'll check if it was a winning move\n");
	return 0;
}

unsigned player()
{
	printf("Here the player will choose his move and will be evaluated (if it's a winning move).\n");
	return 0;
}

unsigned computer ()
{
	printf("Here the computer will choose his move and will be evaluated\n");
	return 0;
}
