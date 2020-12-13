#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct file
{
    char name[100];
    long size;
}file;


void archive(FILE *fp_arch, FILE *fp_file, int file_num, char *name)
{
    fseek(fp_file, 0, SEEK_END);
    long size = ftell(fp_file);
    fseek(fp_file, 0, SEEK_SET);

    file new;
    strcpy(new.name, name);
    new.size = size;

    fwrite(&new, sizeof(file), 1, fp_arch);     //we write the name and the size

    char *buffer = (char*)malloc(size);         //we declare a buffer to read the file
    if (!buffer)
    {
        printf("Could not allocate memory\n");
        exit(4);
    }

    fread(buffer, size, 1, fp_file);
    fwrite(buffer, size, 1, fp_arch);           //read the file and append it in the archive

    free(buffer);
}

int choose_menu()
{
    int key;

    printf("What would you like to do?\n");
    printf("0. Exit\n");
    printf("1. Concatenate the files given as command line arguments\n");
    printf("2. List the files\n");
    printf("3. Extract a file\n");

    scanf("%d", &key);

    return key;

}

void archiving_files(int argc, char **argv, FILE *fp_arch, FILE *fp_file)
{
    for (int i = 2; i < argc; i++)
    {
        fp_file = fopen (argv[i], "rb");

        if (!fp_file)
        {
            printf("Couldnt open file %s\n", argv[i]);
            exit(3);
        }

        fseek(fp_arch, 0, SEEK_END); //we do this before the archiving function so we ensure it appends and doesn't overwrite
        archive(fp_arch, fp_file, i-2, argv[i]);

        fclose(fp_file);
    }

}

int list_files (FILE *fp_arch)
{
    file temp;
    int found = 0;
    long position = 0;

    fseek(fp_arch, 0, SEEK_SET);

    while(fread(&temp, sizeof(file), 1, fp_arch))   //since all temp entries are the same size and contain the size we know 
    {                                               //this will read until the last one inclusive
        found = 1;

        position += temp.size;                      
        position += sizeof(temp);

        printf("%s\n", temp.name);

        fseek(fp_arch, position, SEEK_SET);
    }

    if (found)
        return 1;

    printf("No files here.\n");
    return -1;
}

void extract(FILE *fp_arch, char*arch_name)
{

    if (list_files(fp_arch) == -1)
        return;

    char name [100];
    printf("What file would you like to extract?\n");

    scanf("%100s", name);

    FILE *fp = fopen (name, "wb");
    if(!fp)
    {
        printf("Couldnt create file\n");
        exit(2);
    }

    FILE *tmp = fopen ("tmp.tmp", "wb");
    if (!tmp)
    {
        printf("Couldnt create file\n");
        exit(3);
    }

    char *buffer = (char*) malloc (1);
    if (!buffer)
    {
        printf("Couldnt allocate memory\n");
        exit(6);
    }
    file temp;

    int position = 0;

    fseek(fp_arch, 0, SEEK_SET);

    while(fread(&temp, sizeof(file), 1, fp_arch))
    {
        position += temp.size;
        position += sizeof(temp);

        buffer = realloc(buffer, temp.size);        //allocate the new size of the buffer (for the current file in reading)
        if (!buffer)
        {
        printf("Couldnt allocate memory\n");
        exit(6);
        }

        memset(buffer, 0, temp.size);

        fread(buffer, temp.size, 1, fp_arch);

        if (strcmp(temp.name,name))                 //if we didnt find the file we need we put it back in the archive
        {
            fwrite(&temp, sizeof(temp), 1, tmp);
            fwrite(buffer, temp.size, 1, tmp);
        }
        else                                        //else we write the new file
            fwrite(buffer, temp.size, 1, fp);

        fseek(fp_arch, position, SEEK_SET);
    }

    fclose(fp);
    fclose(tmp);
    fclose(fp_arch);

    remove(arch_name);
    rename("tmp.tmp", arch_name);           //we make the new archive

    fp_arch = fopen (arch_name, "rb+");

    free(buffer);
}


int main (int argc, char**argv)
{
    if (argc < 2)
    {
        printf("Please use command line arguments like this:\n");
        printf("%s <archive name.arh> <file 1> <file 2> [...]\n", argv[0]);
        exit(1);
    }

    FILE *fp_arch = fopen (argv[1], "ab+");
    if (!fp_arch)
    {
        printf("Couldn't open arh file\n");
        exit(2);
    }

    FILE *fp_file = NULL;

    int menu;

    do
    {
        menu = choose_menu();

        switch (menu)
        {
        case 0:
            break;

        case 1:

            archiving_files(argc, argv, fp_arch, fp_file);

            break;

        case 2:

            list_files (fp_arch);

            break;

        case 3:

            extract(fp_arch, argv[1]);

            break;
        }


    }
    while(menu);

    fclose (fp_arch);
    return 0;
}
