#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fill_buffer(FILE *fp, long size, char*buff)
{
    int i=-1;

    while ((buff[++i]=fgetc(fp) )!= EOF)
        if (isalpha(buff[i]) && buff[i] >= 'Z')
            buff[i] = toupper(buff[i]);

    buff[i] = 0;
}

int main(int argc, char**argv)
{
    if (argc<2)
    {
        printf("Format: %s <name_of_file>", argv[0]);
        exit(2);
    }

    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        printf("Couldn't open file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);

    long size = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    char buffer[size+1];

    fill_buffer(fp,size,buffer);

    fclose(fp);

    fp = fopen(argv[1], "w");

    if (!fp)
    {
        printf("couldn't reopen file");
        exit(3);
    }

    fprintf(fp, "%s", buffer);

    fclose(fp);

    return 0;
}
