#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void print_board()
{
	printf("Here we print a board\n");
}


void print_hello ()
{
	printf("Welcome to 3d Tic Tac Toe\n");

}

void display_rules()
{
	printf("Rules:\n\n");
	printf("A cube has 6 faces, on each face there is a 3x3 board.\n");
	printf("Each layer is counted in the order that it appears (0,1,...5).\n");
	printf("In order to choose where to place X or 0, please use this format:\n");
	printf("[Layer number] [i] [j], where i and j are the coordinates in a 3x3 matrix (starting from 0)\n");
	printf("If you wish to choose the center of the cube, please insert only '1'.\n");
	printf("Game is played with normal rules of Tic Tac Toe on every surface with the addition of the element in the cube-center\n");
	printf("You also win if you have corner, cube-center, opposite corner\n\n");
}

void game ()
{
	printf("here we play the game.\n");
}

void menu()
{
	printf("here we display a menu\n");
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
