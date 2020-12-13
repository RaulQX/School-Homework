#include <stdio.h>
#include <stdlib.h>

void open_errors()
{
    printf("Couldn't open the file\n");
    exit(1);
}

unsigned compare (FILE *fp, FILE *fp2, unsigned *length)
{
    char file1;
    char file2;

    int difference = 0;

    while ((file1 = fgetc(fp)) != EOF)
    {
        (*length)++;
        file2 = fgetc(fp2);

        if (file1 != file2)
            difference++;
    }

    if ((file2 = fgetc(fp2))!=EOF)
    {
        printf("Files are of different length\n");
        exit(2);
    }

    return difference;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Format: %s <file1> <file 2>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen (argv[1], "r");
    if (!fp)
        open_errors();

    FILE *fp2 = fopen (argv[2], "r");
    if (!fp2)
        open_errors();

    unsigned difference;
    unsigned total_no=0;
    float percentage;

    difference = compare(fp, fp2, &total_no);
    printf("Hamming distance: %d\n", difference);

    percentage = (float) difference / (float) total_no * 100;
    printf("Files are %.2f%% different\n", percentage);

    fclose(fp);
    fclose(fp2);


    return 0;
}
