#include <stdio.h>
#include <string.h>
#include <limits.h>

/* ########################## MAZE FORMAT ##########################
   First triplet of numbers are the dimensions of maze (maze[o][n][m])
   Attention here, the o is the floor level!
   Second triplet of numbers are the coordinates of the starting point
   Next is the maze, where F is the finish point
   If you want you can print the maze route with X by eliminating the
   comments in the code.
   ########################## MAZE FORMAT ##########################  */

unsigned n,m,o;
int shortest_counter = INT_MAX;
int counter;
int sw;

typedef struct iji
{
    int i;
    int j;
    int k;
} iji;

void print_maze_c(int maze[o][n][m])
{
    for (int k=0; k<o; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
                printf("%c ", maze[k][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    printf("\n");
}


void copy_maze(int shortest_sol[o][n][m], int maze[o][n][m])
{
    for (int level=0; level<o; level++)
        for (int line=0; line<n; line++)
            for (int coll = 0; coll < m; coll ++)
                shortest_sol[level][line][coll] = maze[level][line][coll];
}

int can_step_here(int k, int i, int j, int maze[o][n][m])
{
    if (i >= 0 && j >= 0 && i <= (n-1) && j <= (m-1) && k >= 0 && k <= (o-1) )
        if ((char)maze[k][i][j] == '.' || (char)maze[k][i][j] == 'F')
            return 1;

    return 0;
}

void baccu_traccu (int map[o][n][m], int i, int j, int k, int maze[o][n][m], int shortest_sol[o][n][m], iji route[], iji shortest_route[n*m])
{
    if( (char)maze[k][i][j] == 'F' )
    {
        sw=1;
        //print_maze_c(maze);
        route[counter].i=i;
        route[counter].j=j;
        route[counter].k=k;
        counter++;

        for (int i=0; i<counter-1; i++)
            printf("(%d, %d, %d) ", route[i].i, route[i].j, route[i].k);
        printf("\n\n");

        if (shortest_counter > counter)
        {
            shortest_counter = counter;
            copy_maze(shortest_sol, maze);

            for (int i=0; i<shortest_counter; i++)
            {
                shortest_route[i].i=route[i].i;
                shortest_route[i].j=route[i].j;
                shortest_route[i].k=route[i].k;
            }

        }

        counter --;
        return;
    }

    if (can_step_here(k, i, j, maze))
    {
        route[counter].i=i;
        route[counter].j=j;
        route[counter].k=k;
        counter++;


        if (maze[k][i][j]!='F')
            maze[k][i][j]='x';

        if (i < n-1)
            baccu_traccu(map, i+1, j, k, maze, shortest_sol, route, shortest_route);
        if (j < m-1)
            baccu_traccu(map, i, j+1, k, maze, shortest_sol, route, shortest_route);
        if (i > 0)
            baccu_traccu(map, i-1, j, k, maze, shortest_sol, route, shortest_route);
        if (j > 0)
            baccu_traccu(map, i, j-1, k, maze, shortest_sol, route, shortest_route);
        if (k > 0)
            baccu_traccu(map, i, j, k-1, maze, shortest_sol, route, shortest_route);
        if (k < o-1)
            baccu_traccu(map, i, j, k+1, maze, shortest_sol, route, shortest_route);


        if (maze[k][i][j] != 'F')
        {
            counter--;
            maze[k][i][j] = '.';
            route[counter].i=0;
            route[counter].j=0;
            route[counter].k=0;
        }
    }
}


int main ()
{
    FILE *fp = fopen ("maze3d.txt", "r");

    fscanf(fp," %u %u %u \n", &n, &m, &o);

    int maze[o][n][m];
    int map[o][n][m];
    int shortest_sol[o][n][m];
    int start_i;
    int start_j;
    int start_k;
    iji route[o*n*m];
    iji shortest_route[o*n*m];

    memset(route, 0, o*n*m*sizeof(iji));
    memset(shortest_route, 0, o*n*m*sizeof(iji));

    fscanf(fp, " %d %d %d \n", &start_i, &start_j, &start_k);

    for (int k=0; k<o; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                fscanf(fp," %c \n", &map[k][i][j]);

    copy_maze(maze,map);


    baccu_traccu(map, start_i, start_j, start_k, maze, shortest_sol, route, shortest_route);

    if (sw)
    {
        printf("Shortest solution\n");
        //print_maze_c(shortest_sol);

        for (int i=0; i < shortest_counter - 1; i++)
            printf("(%d, %d, %d) ", shortest_route[i].i, shortest_route[i].j, shortest_route[i].k);
    }
    else
        printf("Sol doesn't exist");


    return 0;
}
