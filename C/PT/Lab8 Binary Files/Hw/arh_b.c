#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void archive(FILE *fp_arch, FILE *fp_file, int file_num, char *name)
{
    fseek(fp_file, 0, SEEK_END);
    long size = ftell(fp_file);
    fseek(fp_file, 0, SEEK_SET);

    fprintf(fp_arch, "\n%s\n%ld\n", name, size);    //note the name and the size to be used later

    char c;

    for (long int i = 0; i < size; i++) //write the new file character by character as requested
    {
        c = fgetc(fp_file);
        if (c != EOF)
            fputc(c, fp_arch);
    }
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
    for (int i = 2; i < argc; i++)  //for each file past the archive
    {
        fp_file = fopen (argv[i], "r");

        if (!fp_file)
        {
            printf("Couldnt open file %s\n", argv[i]);
            exit(3);
        }
        fseek(fp_arch, 0, SEEK_END);    //to append at the archive
        archive(fp_arch, fp_file, i-2, argv[i]);

        fclose(fp_file);
    }
}

int list_files (FILE *fp_arch)
{
    char buffer_name[100];
    char buffer_size[100];

    long size_file;
    long size_arch;
    long pos=0;

    fseek(fp_arch, 0, SEEK_END);
    size_arch = ftell(fp_arch);
    fseek(fp_arch, 0 , SEEK_SET);

    if (size_arch == 0)
    {
    	printf("No files were archived\n");
    	return -1;
    }

    while (pos < size_arch)
    {
        memset(buffer_name, 0, 100);    //reset the buffers at each iteration to avoid trouble
        memset(buffer_size,0, 100);

        fgetc(fp_arch); // the \n i append at the beginning
        
        fgets(buffer_name, 100, fp_arch);

        fgets(buffer_size, 100, fp_arch);
        sscanf(buffer_size, "%ld", &size_file);

        pos+=size_file;             //here we add the size, the name and the lenght of the size i write for each file
        pos+=strlen(buffer_name);
        pos+=strlen(buffer_size); 
        pos+=1; //the \n i append at the name

        printf("%s", buffer_name);

        fseek(fp_arch, pos, SEEK_SET);
    }
    return 1;
}

void extract(FILE *fp_arch, char*arch_name)
{
	
	if (list_files(fp_arch) == -1)
		return;

	char name [100];
	printf("What file would you like to extract?\n");

	scanf("%100s", name);

	FILE *fp = fopen (name, "w");
	if(!fp)
	{
		printf("Couldnt create file\n");
	}

	FILE *tmp = fopen ("tmp.tmp", "w");
	if (!tmp)
	{
		printf("Couldnt create file\n");
	}

	fseek(fp_arch, 0, SEEK_SET);

    char buffer_name[100];
    char buffer_size[100];

    long size_file;
    long size_arch;
    long pos=0;

    fseek(fp_arch, 0, SEEK_END);
    size_arch = ftell(fp_arch);

    fseek(fp_arch, 0 , SEEK_SET);

    char c;
    int switcher = 0;
    int found = 0;

    while (pos < size_arch) //In this while we read all the archive file. Then we split it by splitting the contents
                            //in 2 files, the new archive and the file to be extracted
    {
        memset(buffer_name, 0, 100);
        memset(buffer_size, 0, 100);

        fgetc(fp_arch); //\n
        
        fgets(buffer_name, 100, fp_arch);

        fgets(buffer_size, 100, fp_arch);
        sscanf(buffer_size, "%ld", &size_file);

        pos+=strlen(buffer_name); 
        pos+=strlen(buffer_size);
       
        for (int i = 0; buffer_name[i]; i++) //since we use fgets we remove the \n at the end (could have used strlen)
        	if (buffer_name[i] == '\n')
        		buffer_name[i] = 0;

        if (strcmp(buffer_name, name)==0)
        {
        	switcher = 1;
        	found = 1;
        }
        else
        	fprintf(tmp, "\n%s\n%ld\n", buffer_name, size_file);
        

        for (int i = 0; i < size_file; i++)
        {
        	c=fgetc(fp_arch);  //\n
        	pos++;

        	if (switcher)  //if we found the file we write the contents in the file to be extracted
        		fputc(c, fp);
        	else
        		fputc(c, tmp);    //else we put it back in the archive
        }

        switcher = 0;
        pos++;
    }

    fclose(tmp);
    fclose(fp);
    fclose(fp_arch);

    if (!found)
    {
    	printf("Couldn't find the file\n");
    	remove(name);
    }

    remove(arch_name);
    rename("tmp.tmp", arch_name);

    fp_arch = fopen(arch_name, "r+");
}


int main (int argc, char**argv)
{
    if (argc < 2)
    {
        printf("Please use command line arguments like this:\n");
        printf("%s <archive name.arh> <file 1> <file 2> [...]\n", argv[0]);
        exit(1);
    }

    FILE *fp_arch = fopen (argv[1], "a+");
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
            fseek(fp_arch, 0, SEEK_END);
        
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
