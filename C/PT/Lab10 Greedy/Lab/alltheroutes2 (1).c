#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define cities 5
#define first_city 1

int map[5][5];

unsigned permutations[5];

unsigned minim=UINT_MAX;

void fill_map()
{
	map[0][0]=-1;
	map[0][1]=174;
	map[0][2]=315;
	map[0][3]=634;
	map[0][4]=544;

	map[1][0]=174;
	map[1][1]=-1;
	map[1][2]=152;
	map[1][3]=544;
	map[1][4]=595;

	map[2][0]=315;
	map[2][1]=152;
	map[2][2]=-1;
	map[2][3]=393;
	map[2][4]=449;

	map[3][0]=634;
	map[3][1]=544;
	map[3][2]=393;
	map[3][3]=-1;
	map[3][4]=388;

	map[4][0]=544;
	map[4][1]=595;
	map[4][2]=449;
	map[4][3]=388;
	map[4][4]=-1;
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

void print_route(unsigned *v)
{
	char s[100];
	
	for (int i =0; i<cities; i++)
		printf("%s -> ", choose_city(permutations[i],s));

	printf(" ");
}


//backtracking


void afis()
 {
	unsigned sum=0;

    print_route(permutations);

	for (int i=0; i<=cities-2; i++)
		sum+=map[permutations[i]][permutations[i+1]];

	printf("%u\n", sum);

	if (minim>sum)
		minim=sum;

}

unsigned condition (unsigned k)
{
	for (int i=0; i<k; i++)
		if (permutations[k] == permutations[i])
			return 0;
	return 1;
}

void back(unsigned k)
{
	for (int i=0; i<=(cities-1); i++)
	{
		permutations[k]=i;
		if (condition(k))
		{
			if (k == (cities-1))// && (permutations[0]==first_city))
				afis();
			else
				back(k+1);
		}

	}
}


void print_route_greedy(unsigned *v)
{
	unsigned k=0;
	int i=0;
	char s[100];

	while(k<cities-1 && i<cities)
	{
        if (v[i]==k)
        {
            k++;
            printf("%s -> ", choose_city(i,s));
            i=0;
        }
        else
            i++;
	}

	for (int i=0; i<cities; i++)
		if (v[i]==cities-1)
			printf("%s.",choose_city(i,s));

	printf("\n");

}


unsigned greedy (unsigned start_city, unsigned *path)
{
	int minimum;
	int i,j;
	int this_city_is_min;
	unsigned distance = 0;
	unsigned visited[cities]={0};
	
	unsigned order=0;
	unsigned current_city=start_city;

	for (i=0; i<cities-1; i++)
	{
        minimum=INT_MAX;
		visited[current_city]++;

		for (j=0; j<cities; j++)
			if ((map[current_city][j] < minimum) && (!visited[j]))
			{
				minimum=map[current_city][j];
				this_city_is_min=j;
			}

		current_city=this_city_is_min;
		distance += minimum;
		path[this_city_is_min]=++order;

	}

	return distance;
}

int main ()
{
	fill_map();
	permutations[0]=1;
	unsigned path[cities] = {0};
	unsigned distance;

	back(1);
	printf("Smallest route distance: %u\n", minim);

	distance=greedy(first_city, path);

	printf("\nGreedy way:\n");
	print_route_greedy(path);
	printf("Greedy solution: %u\n", distance);

	return 0;
}
