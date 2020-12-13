#include <stdio.h>
#include <stdlib.h>
#define N 8

int start_i=0;
int start_j=0;
int switcher=0;

typedef struct directie
{
    int deltaY[8];
    int deltaX[8];

} directie;

directie director = { {2, 1, -1, -2, -2, -1, 1, 2}, {1, 2, 2, 1, -1, -2, -2, -1} };

void initialize_board (int board[][N])
{
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            board[i][j]=-1;

    board[start_i][start_j]=0;
}

void print_board (int board[][N])
{
    if (!switcher)
    {
        switcher++;
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (board[i][j]<0)
                    printf("%d ", board[i][j]);

                else if (board[i][j]>=0 && board[i][j]<=9)
                    printf(" %d ", board[i][j]);

                else
                    printf("%d ", board[i][j]);
            }

            printf("\n");
        }
    }
}

int is_it_done(int board[][N])
{
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            if (board[i][j]==-1)
                return 0;

    return 1;
}

int cond (int i, int j, int board[][N])
{
    if (i>=0 && j>=0 && i<N && j<N)
        if (board[i][j]==-1)
            return 1;

    return 0;
}

void bacctraccking(int I, int J, int board[][N], unsigned counter)
{
    int future_i=0, future_j=0;

    for(int i=0; i<8; i++)
    {
        future_i = I + director.deltaY[i];
        future_j = J + director.deltaX[i];

        if (cond(future_i, future_j, board))
        {
            board[future_i][future_j]=counter;

            if (is_it_done(board))
                print_board(board);
            else
            {
                bacctraccking(future_i, future_j, board, counter+1);
                board[future_i][future_j]=-1; //step back
            }

        }

    }
}



int main ()
{
    int board[N][N];


    initialize_board(board);

    //print_board(board);

    bacctraccking(start_i,start_j,board, 1);

    return 0;
}
