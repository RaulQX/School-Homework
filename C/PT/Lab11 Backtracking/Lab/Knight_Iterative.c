#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

//Pe pc-ul meu a durat ~10 minute executia.


int start_i=0;
int start_j=0;
int max_step=0;

typedef struct directie
{
    int deltaY[8];
    int deltaX[8];

} directie;

directie director = { {2,1,-1,-2,-2,-1,1,2}, {1,2,2,1,-1,-2,-2,-1} };

void initialize_matrix(int mat[][N])
{
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            mat[i][j] = -1;

    mat[start_i][start_j]=0;
}

void print_board(int board[][N])
{
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
    printf("\n");
}

int check_valid_move(int I, int J,int mat[][N])
{
    if (I>=0 && I<N && J>=0 && J<N)
        if (mat[I][J] == -1)
            return 1;

    return 0;
}

void tentativa_de_back(int I, int J,int mat[][N])
{
    int contor=1;   //marks the path

    int k=0;        //stiva

    int x=-1;       //numarul miscarii

    int evalid=0;  //validitatea miscarii

    int new_i;      //noile coordonate
    int new_j;

    int moves[N*N]={0};     //vectorul in care construim solutia

    int iterations_back;    //contor deoarece dureaza foarte mult executia
    int first_iterations_ago;   //de asemenea contor

    while (k>=0)
    {
        x=moves[k]; // start from where we left over
        do
        {
            x++;

            new_i = I + director.deltaY[x];
            new_j = J + director.deltaX[x];

            evalid = check_valid_move(new_i, new_j, mat);

        }while (x<=8 && !evalid);

        if (x<=8)
        {
            if (contor == N*N - 1)
            {
                 mat[new_i][new_j]=contor++;

                 print_board(mat);
                 printf("Finished!");

                 return;
            }

            else
            {
                if (contor >= max_step)
                {
                    if (contor > max_step)
                        first_iterations_ago=1;

                    max_step=contor;

                    iterations_back=1;
                }

                moves[k]=x;

                I = new_i;
                J = new_j;

                mat[new_i][new_j]=contor++;

                print_board(mat);
                printf("Max step reached until now: %d, %d iterations ago (first time %d iterations ago)",
                       max_step, iterations_back++, first_iterations_ago++);
                printf("\n");

                k++;
                x=-1;
            }

        }
        else //turning back one step and trying with the other possibilities
        {
            mat[I][J] = -1;

            //print_board(mat); //if you want to see how it goes back

            moves[k]=0;
            k--;

            I -= director.deltaY[moves[k]];
            J -= director.deltaX[moves[k]];

            contor--;
        }

    }

}


int main()
{
    int board[N][N];

    initialize_matrix(board);

    tentativa_de_back(start_i, start_j, board);

    return 0;
}
