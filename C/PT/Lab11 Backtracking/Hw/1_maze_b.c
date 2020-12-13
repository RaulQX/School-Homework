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

void print_maze_c(int maze[][m])
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
            printf("%c ", maze[i][j]);
        printf("\n");
    }

    printf("\n");
}

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

void baccu_traccu (int map[][m], int i, int j, int maze[][m], int shortest_sol[][m])
{
    if( (char)maze[i][j] == 'F' )
    {
        sw=1;

        print_maze_c(maze);

        if (shortest_counter > counter)
        {
            shortest_counter = counter;
            copy_maze(shortest_sol, maze);
        }

        //counter --;
        return;
    }

    if (can_step_here(i, j, maze))
    {
        counter++;

        if (maze[i][j]!='F')
            maze[i][j]='x';

        if (i < n-1)
            baccu_traccu(map, i+1, j, maze, shortest_sol);
        if (j < m-1)
            baccu_traccu(map, i, j+1, maze, shortest_sol);
        if (i > 0)
            baccu_traccu(map, i-1, j, maze, shortest_sol);
        if (j > 0)
            baccu_traccu(map, i, j-1, maze, shortest_sol);

        if (maze[i][j] != 'F')
        {
            counter--;
            maze[i][j] = '.';
        }
    }
}


int main ()
{
    FILE *fp = fopen ("maze.txt", "r");

    fscanf(fp," %u %u \n", &n,&m);

    int maze[n][m];
    int map[n][m];
    int shortest_sol[n][m];
    int start_i;
    int start_j;

    fscanf(fp, " %d %d \n", &start_i, &start_j);

    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            fscanf(fp," %c \n", &map[i][j]);

    copy_maze(maze,map);

    baccu_traccu(map, start_i, start_j, maze, shortest_sol);

    if (sw)
    {
        printf("Shortest solution\n");
        print_maze_c(shortest_sol);
    }
    else
        printf("Sol doesn't exist");

    return 0;
}
