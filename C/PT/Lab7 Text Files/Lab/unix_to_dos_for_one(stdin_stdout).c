#include <stdio.h>
#include <stdlib.h>

void unixtodos()
{
    char c;
    while ((c=fgetc(stdin)) != EOF)
    {
        if (c == '\n')
            fprintf(stdout, "%c", '\r');
        fprintf(stdout, "%c", c);
    }
}

int main()
{

    unixtodos();

    return 0;
}
