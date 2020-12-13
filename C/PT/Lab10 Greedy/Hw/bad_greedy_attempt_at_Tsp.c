#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define cities 5
#define start_city 0

int map[cities][cities];
unsigned visited[cities];

void read(FILE *fp)
{
    fseek(fp,0,SEEK_SET);

    for (int i=0; i<cities; i++)
        for (int j=0; j<cities; j++)
            fscanf(fp,"%d", &map[i][j]);
}

void show_map()
{
    for (int i=0; i<cities; i++)
    {
        for (int j=0; j<cities; j++)
            printf("%d ", map[i][j]);
        printf("\n");
    }

}

char* choose_city(int i, char*s)
{
    memset(s,0,100);

    switch (i)
    {
    case 0:
        strcpy(s,"Timisoara");
        return s;
        break;
    case 1:
        strcpy(s,"Oradea");
        return s;
        break;
    case 2:
        strcpy(s,"Cluj-Napoca");
        return s;
        break;
    case 3:
        strcpy(s,"Iasi");
        return s;
        break;
    case 4:
        strcpy(s,"Bucuresti");
        return s;
        break;
    default:
        strcpy(s, "You shouldn't see this");
        return s;
    }
}

int f_minimum (int c_city)
{
    int minim=INT_MAX;
    int tab;

    for (int i=0; i < cities; i++)
        if ((visited[i]==0) && (map[c_city][i] > 0) && (map[c_city][i] < minim))
        {
            minim=map[c_city][i];
            tab=i;
        }

    if (minim != INT_MAX)
        return tab;
    else
        return -1;
}

unsigned ordering[cities];

int arr_max (unsigned *order)
{
    int maxim= INT_MIN;
    int max_pos;

    for (int i=0; i<cities; i++)
    {
        if ((int)order[i]>maxim)
        {
            maxim=order[i];
            max_pos=i;
        }
    }

    return max_pos;
}

int second_arr_max (unsigned *order)
{
    int max1=0;
    int max2=0;
    int maxim=0;

    for (int i=0; i<cities; i++)
        if (order[i]>maxim)
        {
            maxim=order[i];
            max2=max1;
            max1=i;
        }

    return max2;
}

unsigned min_arr(unsigned *order)
{
    int minim= INT_MAX;
    int minim_pos;

    for (int i=0; i<cities; i++)
        if (order[i]<minim)
        	if (order[i]!=0)
        	{
            	minim=order[i];
            	minim_pos=i;
        	}

    if (minim!=INT_MAX)
    	return minim_pos;

    else 
    	return 0;

}
void print_route_greedy()
{
    char s[100];
    unsigned copy_ordering[cities];

    printf("%s -> ", choose_city(start_city,s));

    for (int i=0; i<cities; i++)
        copy_ordering[i]=ordering[i];

    for (int i=0; i<cities-1; i++)
        if (copy_ordering[(min_arr(copy_ordering))]!=0)
        {
            printf("%s -> ", choose_city(min_arr(copy_ordering),s));
            copy_ordering[min_arr(copy_ordering)]=0;
        }

}

unsigned is_full(unsigned *order)
{
    for (int i=0; i<cities; i++)
    {
        if (order[i]==0)
            if (i!=start_city)
                return 0;
    }

    return 1;
}

unsigned calculate_distance()
{
    unsigned distance = 0;
    int i,j;

    for (i=0; i<cities; i++)
    {
        for (j=0; j<cities; j++)
            if (ordering[j]==ordering[i]+1)
                distance+=map[i][j];
    }

    return distance;
}

unsigned order=1;
unsigned max_pos=-1;
unsigned big_switch;
unsigned contor=0;

void greedy(int curr_city)
{
    if (!big_switch)
    {
        int new_city;
        int i;
        unsigned second_max_pos;

        for (i=0; i<cities-1 && !big_switch; i++)
        {
            visited[curr_city]++;

            new_city=f_minimum(curr_city);

            if(max_pos != -1)
                visited[max_pos]=0;

            print_route_greedy();
            printf("\n");

            if (is_full(ordering))
                big_switch=1;

            if (new_city != -1 && (!big_switch))
            {
                ordering[new_city]=order++;
                contor++;

                curr_city=new_city;
            }
            else if (!big_switch)
            {
                max_pos=arr_max(ordering);
                second_max_pos=second_arr_max(ordering);

                ordering[max_pos]=0;
                order--;
                contor--;

                greedy(second_max_pos);
            }

        }//for ends here

    }//if(switch) ends here
}


int main (int argc, char*argv[])
{
    if (argc!=2)
    {
        printf("Please give the map as command line argument\n");
        exit(1);
    }

    FILE *fp = fopen (argv[1], "r");

    if (!fp)
    {
        printf("Please insert the right name for the file\n");
        exit(2);
    }

    read(fp);
    //show_map();

    greedy(start_city);

    print_route_greedy();

    printf("%u.\n", calculate_distance(ordering));

    return 0;
}

