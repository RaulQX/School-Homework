#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unixtodos(char *filename)
{
    FILE *fp_in = fopen (filename, "r");
    if (!fp_in)
    {
        printf("Could not open %s", filename);
        exit(2);
    }

    int i;
    int k=0;

    char new_name[50];

    for (i=0; filename[i]; i++)
        if (filename[i]=='.')
            k=i;

    strcpy(new_name, filename);

    if ( (i==strlen(filename)) && (k==0) )
        strcpy(new_name + i, ".dos");

    else
        strcpy(new_name + k, ".dos");

    FILE *fp_out = fopen(new_name, "w");
    if (!fp_out)
    {
        printf("Could not create file");
        exit(4);
    }

    char c;
    while ((c=fgetc(fp_in)) != EOF)
    {
        if (c == '\n')
            fprintf(fp_out, "%c", '\r');
        fprintf(fp_out, "%c", c);
    }

    fclose(fp_in);
    fclose(fp_out);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Please give the files as command line arguments");
        exit(1);
    }

    for (int i=1; i<argc; i++)
        unixtodos(argv[i]);

    return 0;
}
