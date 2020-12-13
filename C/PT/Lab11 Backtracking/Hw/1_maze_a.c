#include <stdio.h>
#include <string.h>
#include <limits.h>

/* ########################## MAZE FORMAT ##########################
   first pair of numbers are the dimensions of maze (maze[n][m])
   second pair of numbers are the coordinates of the starting point
   next is the maze, where F is the finish point
   ########################## MAZE FORMAT ##########################  */

unsigned n,m;
int shortest_counter = INT_MAX;
int counter;
int sw;

typedef struct iji
{
    int i;
    int j;

} iji;

void copy_maze(int shortest_sol[][m], int maze[][m])
{
    for (int line=0; line<n; line++)
        for (int coll = 0; coll < m; coll ++)
            shortest_sol[line][coll] = maze[line][coll];
}

int can_step_here(int i, int j, int maze[n][m])
{
    if (i >= 0 && j >= 0 && i <= (n-1) && j <= (m-1))
        if ((char)maze[i][j] == '.' || (char)maze[i][j] == 'F')
            return 1;

    return 0;
}

void baccu_traccu (int map[][m], int i, int j, int maze[][m], iji route[], iji shortest_route[n*m])
{
    if( (char)maze[i][j] == 'F' )
    {
        sw=1;
        route[counter].i=i;
        route[counter].j=j;
        counter++;

        for (int i=0; i<counter-1; i++)
            printf("(%d, %d) ", route[i].i, route[i].j);
        printf("\n\n");

        if (shortest_counter > counter)
        {
            shortest_counter = counter;

            for (int i=0; i<shortest_counter; i++)
            {
                shortest_route[i].i=route[i].i;
                shortest_route[i].j=route[i].j;
            }

        }

        counter --;
        return;
    }

    if (can_step_here(i, j, maze))
    {
        route[counter].i=i;
        route[counter].j=j;
        counter++;


        if (maze[i][j]!='F')
            maze[i][j]='x';

        if (i < n-1)
            baccu_traccu(map, i+1, j, maze, route, shortest_route);
        if (j < m-1)
            baccu_traccu(map, i, j+1, maze, route, shortest_route);
        if (i > 0)
            baccu_traccu(map, i-1, j, maze, route, shortest_route);
        if (j > 0)
            baccu_traccu(map, i, j-1, maze, route, shortest_route);

        if (maze[i][j] != 'F')
        {
            counter--;
            maze[i][j] = '.';
            route[counter].i=0;
            route[counter].j=0;
        }
    }
}


int main ()
{
    FILE *fp = fopen ("maze.txt", "r");

    fscanf(fp," %u %u \n", &n,&m);

    int maze[n][m];
    int map[n][m];
    int start_i;
    int start_j;
    iji route[n*m];
    iji shortest_route[n*m];

    memset(route, 0, n*m*sizeof(iji));
    memset(shortest_route, 0, n*m*sizeof(iji));

    fscanf(fp, " %d %d \n", &start_i, &start_j);

    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            fscanf(fp," %c \n", &map[i][j]);

    copy_maze(maze,map);

    baccu_traccu(map, start_i, start_j, maze, route, shortest_route);

    if (sw)
    {
        printf("Shortest solution\n");

        for (int i=0; i < shortest_counter - 1; i++)
            printf("(%d, %d) ", shortest_route[i].i, shortest_route[i].j);
    }
    else
        printf("Sol doesn't exist");


    return 0;
}
