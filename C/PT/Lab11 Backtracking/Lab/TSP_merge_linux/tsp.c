#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define map_dims 5

enum {timisoara, oradea, cluj_napoca, iasi, bucuresti};
char *cities[] = {"Timisoara", "Oradea", "Cluj-Napoca", "Iasi", "Bucuresti"};
unsigned minimum_distance = INT_MAX;
unsigned minimum_order[map_dims];
unsigned visited[map_dims] = {0};

int check_visited (unsigned *visited)
{
	for (int i = 0; i < map_dims; i++)
	{
		if (visited[i] == 0)
			return -1;
	}

	return 1;
}

int verify_all(unsigned *order)
{
	for (int i = 0; i < map_dims; i++)
	{
		if (order[i] == (map_dims - 1))
			return 1;
	}


	return 0;
}

unsigned calculate_distance (unsigned *route, unsigned map[][map_dims])
{
	unsigned sum = 0;

	for (int i = 0; i < map_dims; i++)
	{
		for (int j = 0; j < map_dims; j++)
		{
			if ( route[j] == (route[i]+1) )
				sum += map[i][j];
		}
	}

	return sum;
}

void copy_order(unsigned *destination, unsigned *from_here)
{
	for (int i = 0; i < map_dims; i++)
		destination[i] = from_here[i];
}



void back(unsigned map[][map_dims], unsigned city, unsigned first_city)
{
	unsigned distance;

	static int order = -1;
	order++;

	for (int i = 0; i < map_dims; i++)
	{
		if (map[city][i] != 0 && visited[i] == 0)
		{
			visited[city] = order;
			back(map, i, first_city);

			distance = calculate_distance(visited, map);

			if ( (verify_all(visited)) && (visited[0] == first_city) && (distance < minimum_distance) )
			{
				minimum_distance = distance;
				copy_order(minimum_order, visited);
			}

			visited[i] = 0;
			order--;

		}
	}
}

void print_minimum_route ()
{
	for (int i = 0; i < map_dims; i++)
		printf("%s ", cities[minimum_order[i]]);
	
	printf("\n");
}


int main (int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Please introduce the map as c l a\n");
		exit(1);
	}

	FILE *fp = fopen (argv[1], "r");
	if (!fp)
	{
		printf("Couldn't open file\n");
		exit(1);
	}

	unsigned map[map_dims][map_dims];

	for (int i  = 0 ; i < map_dims; i++)
	{
		for (int j = 0; j < map_dims; j++)
			fscanf(fp,"%u ", &map[i][j]);
	}

	fclose(fp);

	back (map, timisoara, timisoara);

	printf("Route:\n");
	print_minimum_route();

	printf("Minimum distance: ");
	printf("%u\n", minimum_distance);


	return 0;
}