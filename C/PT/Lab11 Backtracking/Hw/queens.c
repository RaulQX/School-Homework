#include <stdio.h>
#define N 8
#define QUEEN 9

void print_board(int board[][N])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if (board[i][j]==0)
                printf("[ ] ");
            else
                printf("[Q] ");
        }
        printf("\n");
    }
    printf("\n");
}

int diagonal(int board[][N], int x, int y)
{
    int i_st_jos=x;
    int j_st_jos=y;

    int i_st_sus=x;
    int j_st_sus=y;

    int i_diag_dr_sus=x;
    int j_diag_dr_sus=y;

    int i_diag_st_jos=x;
    int j_diag_st_jos=y;

    while (i_st_sus>0 && j_st_sus>0)
    {
        i_st_sus--;
        j_st_sus--;

        if (board[i_st_sus][j_st_sus] == QUEEN)
            return 0;
    }

    while (i_st_jos < N-1 && j_st_jos < N-1)
    {
        i_st_jos++;
        j_st_jos++;

        if (board[i_st_jos][j_st_jos] == QUEEN)
            return 0;
    }

    while (i_diag_dr_sus > 0 && j_diag_dr_sus < N -1 )
    {
        i_diag_dr_sus--;
        j_diag_dr_sus++;

        if (board[i_diag_dr_sus][j_diag_dr_sus] == QUEEN)
            return 0;
    }

    while (i_diag_st_jos < N -1 && j_diag_st_jos > 0)
    {
        i_diag_st_jos++;
        j_diag_st_jos--;

        if (board[i_diag_st_jos][j_diag_st_jos]==QUEEN)
            return 0;
    }

    return 1;
}

int vertical(int board[][N], int x, int y)
{
    int a=x;

    while (a>0)
    {
        a--;
        if (board[a][y]==QUEEN)
            return 0;
    }

    while (x<N-1)
    {
        x++;
        if (board[x][y]==QUEEN)
            return 0;
    }

    return 1;
}

int horizontal (int board[][N], int x, int y)
{
    int b=y;

    while (b>0)
    {
        b--;
        if (board[x][b]==QUEEN)
            return 0;
    }

    while (y<N -1)
    {
        y++;
        if (board[x][y]==QUEEN)
            return 0;
    }

    return 1;
}

int condition(int board[][N], int x, int y)
{
    if ( (diagonal(board,x,y)) && (vertical(board,x,y)) && (horizontal(board,x,y)) )
        return 1;

    return 0;
}

void backktrakk_queens(int board[][N], int k)
{
    for (int i=0; i < N; i++)
    {
        board[i][k]=QUEEN;

        //print_board(board);

        if (condition(board,i,k))
        {
            if (k < N - 1)
                backktrakk_queens(board, k+1);
            else
                print_board(board);
        }
        board[i][k] = 0;
        //print_board(board);
    }
}

int main()
{
    int board[N][N] = {{0}};

    backktrakk_queens(board, 0);

    return 0;
}
