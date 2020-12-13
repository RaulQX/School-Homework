#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define map_dims 5

enum {timisoara, oradea, cluj_napoca, iasi, bucuresti};
char *cities[] = {"Timisoara", "Oradea", "Cluj-Napoca", "Iasi", "Bucuresti"};

int check_visited (unsigned *visited)
{
	for (int i = 0; i < map_dims; i++)
		if (visited[i] == 0)
			return -1;

	return 1;
}

unsigned visited[map_dims] = {0};

void greedy_tsp(unsigned map[][map_dims], unsigned city, unsigned *distance)
{
	static int counter = 1;

	unsigned local_min = INT_MAX;
	unsigned future_city;

	printf("%d. %s\n", counter++, cities[city]);
	visited[city]++;

	if (check_visited(visited) < 0)
	{
		for (int i = 0; i < map_dims; i++)
			if ( (map[city][i] != 0) && (map[city][i] < local_min) && (visited[i] == 0) )
			{
				local_min = map[city][i];
				future_city = i;
			}

		(*distance) += local_min;
		greedy_tsp(map, future_city, distance);

	}
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
	unsigned distance = 0;

	for (int i  = 0 ; i < map_dims; i++)
		for (int j = 0; j<map_dims; j++)
			fscanf(fp,"%u ", &map[i][j]);

	/*for (int i  = 0 ; i < map_dims; i++)
	{
		for (int j = 0; j<map_dims; j++)
			printf("%u ", map[i][j]);
		printf("\n");
	}*/

	fclose(fp);

	greedy_tsp (map, oradea, &distance);

	printf("Total distance travelled by greedy method: %u\n", distance);

	return 0;
}