#include <stdio.h>
#include <string.h>

/* Read 2 strings, print the longest common substring and its length
   Keep in mind the \n at the end */

int long_com_substr (char *s1, char *s2, char *sol)
{
    int n = strlen (s1);
    int m = strlen (s2);

    int sol_mat[n+1][m+1];

    int sol_i;

    int maxim=0;

    memset(sol_mat, 0, sizeof(int)*(n+1)*(m+1));

    for (int i=1; i<=n; i++)
        for (int j=1; j<m; j++)
            if (s1[i-1]==s2[j-1])
            {
                sol_mat[i][j] = sol_mat[i-1][j-1] + 1;
                if (sol_mat[i][j] > maxim)
                {
                    maxim = sol_mat[i][j];
                    sol_i = i;
                }
            }

    //Uncomment to see the matrix
    /*
    for (int i = 0; i < n; i++)
    {
        for (int j=0; j<m; j++)
            printf("%d ", sol_mat[i][j]);
        printf("\n");
    }

    printf("\n");
    */

    int contor = maxim;

    while (contor>=0)
        sol[contor--]=s1[sol_i--];

    sol[maxim]=0;

    return maxim;
}


int main ()
{
    char s1[300];
    char s2[300];
    char sol[300];

    fgets(s1,300,stdin);
    fgets(s2,300,stdin);

    int answ = long_com_substr(s1, s2, sol);

    printf("Longest substring is: \n%s \n%d characters\n",sol, answ);

    return 0;
}
