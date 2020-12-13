#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { mainsq, binary, variable }sts;

typedef struct {
	unsigned int age : 3;
	char color[12];
}main_seq_t;

typedef struct {
	double rad_st1;
	double rad_st2;
}bin_t;

typedef struct {
	long double min_luminosity;
	long double max_luminosity;
	long double light_periodicity;
	
}var_light;

typedef union {
	main_seq_t main;
	bin_t binary;
	var_light variable_light;
}star_type;

typedef struct {
	unsigned int type : 2;
	char name[100];
	star_type star_details;
}stars;

stars getname (stars x)
{
	printf("Please introduce the name of the star.\n");
	scanf("%100s",x.name);
	return x;
}

stars read_data(unsigned key)
{
	stars x;
	unsigned age;

	x.type=key;

	x=getname(x);

	switch (x.type)
	{
		
		case mainsq:

			printf("Please introduce the age category of the star [1,2,3,4]: ");
			scanf("%u",&age);
			if (age>=1 && age<=4)
				x.star_details.main.age=age;
			else 
			{
				printf("Age must be an integer from one to four!\n");
				exit(1);
			}

			printf("Please introduce the colour of the star.\n");
			scanf("%12s", x.star_details.main.color);
			break;

		case binary:

			printf("Please introduce the first rotation radius of the binary system: ");
			scanf("%lf", &x.star_details.binary.rad_st1);

			printf("Now please introduce the other rotation radius: ");
			scanf("%lf", &x.star_details.binary.rad_st2);

			if (x.star_details.binary.rad_st1 <0 || x.star_details.binary.rad_st2 <0)
			{
				printf("Radius must not be negative!\n");
				exit(2);
			}

			break;

		case variable:

			printf("Please introduce the minimum luminosity: \n");
			scanf("%Lf", &x.star_details.variable_light.min_luminosity);


			printf("Please introduce the maximum luminosity: \n");
			scanf("%Lf", &x.star_details.variable_light.max_luminosity);

			if (x.star_details.variable_light.min_luminosity > x.star_details.variable_light.max_luminosity)
			{
				printf("Minimum luminosity cannot be greater than maximum luminosity!\n");
				exit (3);
			}

			printf("Please introduce the light periodicity in earth days.\n");
			scanf("%Lf", &x.star_details.variable_light.light_periodicity);

			if (x.star_details.variable_light.light_periodicity < 0)
			{
				printf("Period can't be smaller than 0\n");
				exit(4);
			}

			break;
	}
	return x;
}

void print_star(stars ourstar)
{
	printf("\nName of the star/system: %s\n", ourstar.name);

	switch (ourstar.type)
	{
		case mainsq:
			printf("Type: Main sequence of stars.\n");
			printf("Age: %u\n", ourstar.star_details.main.age);
			printf("Color: %s\n", ourstar.star_details.main.color);

		break;

		case binary:
			printf("Type: Binary system of stars.\n");
			printf("Rotation radius 1: %lf\n", ourstar.star_details.binary.rad_st1);
			printf("Rotation radius 2: %lf\n", ourstar.star_details.binary.rad_st2);

		break;

		case variable:
			printf("Type: Variable light stars.\n");
			printf("Minimum luminosity: %Lf\n", ourstar.star_details.variable_light.min_luminosity);
			printf("Maximum luminosity: %Lf\n", ourstar.star_details.variable_light.max_luminosity);
			printf("Light periodicity: %Lf\n", ourstar.star_details.variable_light.light_periodicity);

		break;
	}

	putchar('\n');
}

int main()
{
	unsigned key;
	stars ourstar;

	printf("What kind of star would you like to introduce?\nMain sequence of stars: [0]\nBinary system of stars: [1]\nVariable light stars: [2]\n");
	scanf("%u",&key);

	if (key >=0 && key <=2)
		ourstar=read_data(key);
	else 
	{
		printf("Not a good value!\n");
		exit(5);
	}

	print_star(ourstar);

	return 0;
}