#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define draw 55

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
	for (i=4; i<=5; i++)
	{
		for (j=0; j<3; j++)
		{
			printf("	   ");
			for (k=0; k<3; k++)
			{
				if (board[i][j][k]==0)
		            printf("[ ]");
	        	if (board[i][j][k]==1)
	            	printf("[X]");
	       		if (board[i][j][k]==2)
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
	printf("If you wish to choose the center of the cube, please insert only [6] [0] [1].\n");
	sleep(1);
	printf("Game is played with normal rules of Tic Tac Toe on every surface with the addition of the element in the cube-center\n");
	sleep(1);
	printf("You also win if you have corner, cube-center, opposite corner and center, cube center, center\n");
	sleep(1);
	printf("Keep imagining that the cube is in 3d, so when you score corner, cube-center, corner it might seem upside down.\n");
	sleep(1);
	printf("An example is [0][0][0], center, [4][0][2].\n\n");
	sleep(1);
}

unsigned check_win (unsigned board_win[6][3][3], unsigned n, unsigned center)
{
	int i;
	for (i=0; i<6; i++)
	{
		if (board_win[i][0][0]==n && board_win[i][0][1]==n && board_win[i][0][2]==n)
	        return 1;
	    if (board_win[i][1][0]==n && board_win[i][1][1]==n && board_win[i][1][2]==n)
	        return 1;
	    if (board_win[i][2][0]==n && board_win[i][2][1]==n && board_win[i][2][2]==n)
	        return 1;

	    if (board_win[i][0][0]==n && board_win[i][1][0]==n && board_win[i][2][0]==n)
	        return 1;
	    if (board_win[i][0][1]==n && board_win[i][1][1]==n && board_win[i][2][1]==n)
	        return 1;
	    if (board_win[i][0][2]==n && board_win[i][1][2]==n && board_win[i][2][2]==n)
	        return 1;

	    if (board_win[i][0][0]==n && board_win[i][1][1]==n && board_win[i][2][2]==n)
	        return 1;
	    if (board_win[i][0][2]==n && board_win[i][1][1]==n && board_win[i][2][0]==n)
	        return 1;
	}

	if (center == n)
	{
		if (board_win[0][1][1]==n && board_win[4][1][1]==n)
			return 1;
		if (board_win[1][1][1]==n && board_win[3][1][1]==n)
			return 1;
		if (board_win[2][1][1]==n && board_win[5][1][1]==n)
			return 1;

		if (board_win[0][0][0]==n && board_win[4][0][2]==n)
			return 1;
		if (board_win[0][0][2]==n && board_win[4][0][0]==n)
			return 1;
		if (board_win[0][2][0]==n && board_win[4][2][2]==n)
			return 1;
		if (board_win[0][2][2]==n && board_win[4][2][0]==n)
			return 1;

		if (board_win[1][0][0]==n && board_win[3][0][2]==n)
			return 1;
		if (board_win[1][0][2]==n && board_win[3][0][0]==n)
			return 1;
		if (board_win[1][2][0]==n && board_win[3][2][2]==n)
			return 1;
		if (board_win[1][2][2]==n && board_win[3][2][0]==n)
			return 1;

		if (board_win[2][0][0]==n && board_win[5][0][2]==n)
			return 1;
		if (board_win[2][0][2]==n && board_win[5][0][0]==n)
			return 1;
		if (board_win[2][2][0]==n && board_win[5][2][2]==n)
			return 1;
		if (board_win[2][2][2]==n && board_win[5][2][0]==n)
			return 1;

	}


	return 0;
}



unsigned player(unsigned board[6][3][3],unsigned *center, unsigned* chosen, unsigned mark)
{
	int i,j,k;
	int pwin;

	if (mark%2==0)
		mark=1;
	else mark=2;

	print_board(board,*center);
	printf("Please choose where to place.\n");
	scanf("%d %d %d", &i, &j, &k);
	if (i>=0 && i<=6 && j>=0 && j<=2 && k>=0 && k<=2 && chosen[9*i+3*j+k]==0)
	{
		chosen[(9*i)+(3*j)+k]++;
		if (i==6 && j==0 && k==1)
		{	
			*center=mark;
		}
		else if (i==6)
		{
			printf("Please try again.\n");
			player(board,center,chosen,mark+1);
		}

		else
		{
			board[i][j][k]=mark;
		}
	}
	else
	{
		printf("Please try again.\n");
		player(board,center,chosen,mark+1);
	}

	pwin=check_win(board,mark,*center);

	if (pwin==1)
	{
		print_board(board, *center);
		printf("Player wins!\n");
	}

	return pwin;
}

unsigned smart_check(unsigned a_board[6][3][3], unsigned *center, unsigned*chosen, unsigned mark)
{

	for (int i=0; i<6; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
			{
				if (a_board[i][j][k]==0 && chosen[(9*i)+(3*j)+k]==0)
				{
					a_board[i][j][k]=mark;
					if (check_win(a_board,mark,*center)==1)
					{
						a_board[i][j][k]=0;
						return ((9*i)+(3*j)+k);
					}
					else
					{
						a_board[i][j][k]=0;
					}
				}
			}

	if (chosen[55]==0)
	{
		*center=mark;
		if (check_win(a_board,mark,*center)==1)
			return 55;
	}

	return 0;

}

int smart_move(unsigned board[6][3][3], unsigned *center, unsigned*chosen, unsigned mark)
{
	unsigned aux_board[6][3][3];
	unsigned aux_center=*center;
	unsigned move;
	unsigned not_mark;
	unsigned *p_aux_c=&aux_center;

	if (mark==1)
		not_mark=2;
	else not_mark=1;

	for (int i=0; i<6; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
				aux_board[i][j][k]=board[i][j][k];

	move=smart_check(aux_board,p_aux_c,chosen,mark);
	if (move!=0)
		return move;

	move=smart_check(aux_board,p_aux_c,chosen,not_mark);
	if (move!=0)
		return move;

	return -1;

}


unsigned computer (unsigned board[6][3][3], unsigned *center, unsigned* chosen, unsigned mark)
{
	unsigned rand_pick;
	int is_ok=0;
	int i,j,k;
	int cwin;
	int smart_pick;

	if (mark%2==0)
		mark=1;
	else mark=2;

	smart_pick=smart_move(board,center,chosen,mark);
	if (smart_pick!=-1)
	{
		chosen[smart_pick]++;
		if (smart_pick==55)
			*center=mark;
		else
		{
			i=smart_pick/9;
			j=(smart_pick-i*9)/3;
			k=(smart_pick-i*9)%3;
			board[i][j][k]=mark;
		}

	}
	else
	{
		while (!is_ok)
		{
			rand_pick=rand()%56;
			if (chosen[rand_pick]==0)
			{
				is_ok=1;
				if (rand_pick == 55)
				{
					*center=mark;
					chosen[rand_pick]++;
				}
				else
				{
					chosen[rand_pick]++;
					i=rand_pick/9;
					j=(rand_pick-i*9)/3;
					k=(rand_pick-i*9)%3;
					board[i][j][k]=mark;
				}

			}
		}
	}

	cwin=check_win(board, mark, *center);

	if (cwin==1)
	{
		print_board(board, *center);
		printf("Computer wins!\n");
	}

	return cwin;
}


void game (unsigned turn)
{
	unsigned board[6][3][3]={{{0}}};
	unsigned chosen[56]={0};

	unsigned centre = 0;
	int is_won=0;
	unsigned to_draw =0;
	int ptry;

	unsigned *pc=&centre;

    if (turn == 1)
        ptry=0;
    else
    {
        ptry=1;
    }

	while (is_won == 0)
	{
		to_draw++;
		turn++;

		if(to_draw==draw)
		{
			printf("draw\n");
			return;
		}
		else
		{
			if (turn %2 == 0)
				is_won=player(board, pc, chosen, ptry);
			else
			{
				is_won=computer(board, pc, chosen, ptry+1);
				
			}
		}
	}
}

void menu()
{
	int key;
	int playerX;
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
	    	printf("Would you like to play first or second? [1/2]\n");
	    	scanf("%d", &playerX);
	    	if (playerX== 1 || playerX == 2)
	    		game(playerX);
	    	else
	    		printf("Wrong input\n");
	        break;
	    case 2:
	    	return;
	    default:
	        printf("Wrong number!\n");
	        break;
	    }
	}
}



