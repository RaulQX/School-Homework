#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define first_city 0

int cities;
int map[5][5];
unsigned route[5];
unsigned minim = UINT_MAX;
unsigned shortest_route[5];

void fill_map()
{
    FILE *fp = fopen("map.txt", "r");
    fscanf(fp, "%d", &cities);
    for (int i=0; i < cities; i++)
        for (int j=0; j < cities; j++)
            fscanf(fp, "%d", &map[i][j]);

}
void show_map()
{
    for (int i=0; i < cities; i++)
    {
        for (int j=0; j < cities; j++)
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

unsigned condition (unsigned k)
{
    for (int i=0; i < k; i++)
        if (route[k] == route[i])
            return 0;

    return 1;
}

void print_route(unsigned *v)
{
    char s[100];

    printf("%s -> ",choose_city(first_city,s));

    for (int i = 1; i < cities; i++)
        printf("%s -> ", choose_city(v[i],s));
}

void select_minimum(unsigned sum)
{
    if (sum < minim)
    {
        minim = sum;
        for (int i=0; i<cities; i++)
            shortest_route[i]=route[i];
    }


}

int verify_v(int *origVector)
{
    int v2[100]={0};

    for (int i=0; i<cities; i++)
    {
        v2[ origVector[i] ]++;
        if (v2[ origVector[i] ] >1)
            return 0;
    }

    return 1;
}

unsigned sum_perm (int *v)
{
    unsigned sum=0;
    unsigned swtch=0;

    if (!verify_v(v))
        swtch=1;

    for (int i=0; i<cities-1; i++)
    {
        sum += map[v[i]][v[i+1]];

        if (map[v[i]][v[i+1]] == -1)
            swtch = 1;
        if (sum > minim)
            swtch = 1;
    }

    if (!swtch)
        return sum;
    else
        return 0;
}



void back(unsigned k)
{
    int sum=0;
    for (int i=0; i<=(cities-1); i++)
    {

        route[k]=i;

        if (condition(k))
        {
            if (route[0]==first_city)
                sum=sum_perm(route);

            if (sum)
                select_minimum(sum);
            else
                back(k+1);
        }

    }
}

void print_min_route()
{
    print_route(shortest_route);
    printf("%u.\n", minim);

}

int main ()
{

    fill_map();
    back(0);
    print_min_route();
    return 0;
}
