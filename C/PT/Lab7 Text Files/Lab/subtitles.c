#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HTMLTAGS 6

//Works with double precision seconds to be added

void format_seconds (char *s)
{
    int i;
    for (i=0; s[i]; i++)
        if (s[i]=='.')
        {
             s[i]=',';
             break;
        }
    s[i+4]=0;
}

void make_time (int *hours, int *minutes, double *seconds, double plus_seconds)
{
    int condition;

    *seconds += plus_seconds;
    if (plus_seconds > 0)
    {
        while(*seconds >= 60)
        {
            (*seconds) -= 60;
            (*minutes) ++;
        }

        while(*minutes >= 60)
        {
            (*minutes) -= 60;
            (*hours) ++;
        }
    }
    else
    {
        while(*seconds < 0)
        {
            (*seconds) += 60;
            (*minutes) --;
        }
        while(*minutes < 0)
        {
            (*minutes) +=60;
            (*hours) --;
        }
        if (*hours < 0)
        {
            printf("Cannot subtract that much time");
            printf("Do you want to continue with negative hours? [1 - yes  0 - no]");
            scanf("%d", &condition);
            if (!condition)
                exit(3);
        }
    }
}

void print_time (int hours, int minutes, char* seconds, FILE *fp2)
{
    if (hours < 10 && hours >= 0)
        fprintf(fp2, "0%d:", hours);
    else
        fprintf(fp2, "%d:", hours);

    if (minutes < 10)
        fprintf(fp2, "0%d:", minutes);
    else
        fprintf(fp2, "%d:", minutes);

    if (atof(seconds) < 10)
        fprintf(fp2, "0%s", seconds);
    else
        fprintf(fp2, "%s", seconds);

}

void format(FILE *fp, char *seconds_plus)
{
    FILE *fp2 = fopen("formatted_subtitle.srt", "w");
    if (!fp2)
    {
        printf("Could not create file\n");
        exit(3);
    }

    double plus_seconds = atof(seconds_plus);

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char continut_in[size];
    int sub_num;

    int hours, hours2;
    int minutes, minutes2;
    double seconds, seconds2;
    double miliseconds, miliseconds2;

    int str_delete_here;

    int line_count=0;

    char secondschar[10];

    char *htmltags[] = {"<b>", "</b>", "<i>", "</i>", "<u>", "</u>"};

    while (fgets(continut_in,size,fp))
    {
        switch (line_count)
        {
        case 0:
            sscanf(continut_in, "%d", &sub_num);

            fprintf(fp2, "%d", sub_num);
            fprintf(fp2, "\n");

            line_count++;

            break;

        case 1:
            sscanf(continut_in, "%2d:%2d:%2lf,%3lf --> %2d:%2d:%2lf,%3lf", &hours, &minutes, &seconds, &miliseconds,
                   &hours2, &minutes2, &seconds2, &miliseconds2);

            seconds += miliseconds/1000;
            seconds2 += miliseconds2/1000;

            make_time(&hours, &minutes, &seconds, plus_seconds);
            make_time(&hours2, &minutes2, &seconds2, plus_seconds);

            sprintf(secondschar, "%lf", seconds);
            format_seconds(secondschar);

            print_time(hours, minutes, secondschar, fp2);

            fprintf(fp2," --> ");

            sprintf(secondschar, "%lf", seconds2);
            format_seconds(secondschar);

            print_time(hours2, minutes2, secondschar, fp2);

            fprintf(fp2, "\n");

            line_count++;

            break;

        case 2:
            if (strcmp(continut_in, "\n")==0)
            {
                fprintf(fp2,"\n");
                line_count=0;
            }
            else
            {
                for (int i=0; i<HTMLTAGS; i++)
                {
                    while (strstr(continut_in, htmltags[i]) !=0 )
                    {
                        str_delete_here = strstr(continut_in, htmltags[i]) - continut_in;

                        if (i%2 == 0)
                            strcpy(continut_in + str_delete_here, continut_in + str_delete_here + 3);
                        else
                            strcpy(continut_in + str_delete_here, continut_in + str_delete_here + 4);
                    }
                }

                fprintf(fp2, "%s", continut_in);
                break;
            }
        }
    }

    fclose(fp2);
}

int main(int argc, char **argv)
{
    FILE *fp = fopen (argv[1], "r");
    if (!fp)
    {
        printf("Please give command line arguments [name_of_file seconds]");
        exit(1);
    }

    format(fp, argv[2]);

    fclose(fp);

    return 0;
}
