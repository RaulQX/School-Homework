#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 7

int main()
{

    double (*fptrs[N]) (double x);
    double num;

    char *names[]={"sin","cos","ceil","floor","fabs","log","sqrt"};

    int k;
    int func_num;

    fptrs[0] = sin;
    fptrs[1] = cos;
    fptrs[2] = ceil;
    fptrs[3] = floor;
    fptrs[4] = fabs;
    fptrs[5] = log;
    fptrs[6] = sqrt;

    while (1)
    {
        printf("Would you like to select a function? [1 for yes, 0 for no]: ");
        scanf("%d", &k);

        if (!k)
            break;

        printf("What function would you like to use?\n");
        printf("0 - sin\n 1 - cos\n 2 - ceil\n 3 - floor\n 4 - fabs\n 5 - log\n 6 - sqrt\n");
        scanf("%d", &func_num);

        printf("Now please introduce a number: ");
        scanf("%lf", &num);

        printf("Result is: %lf\n", fptrs[func_num](num));
    }



    return 0;
}
