#include <stdio.h>
#include <stdlib.h>

// Yes, I know this is A LOT of code, but it's mostly because I'm using a lot of functions and using switches

typedef enum { insect, bird, mammal, fish }ans;
typedef enum { permanent_t, short_distance_t, medium_distance_t, long_distance_t, other_t}habits;
typedef enum { add, delete, replace, lookup, getout=-1}menu;

typedef struct {
	unsigned int legs;
	double life_span;
}insect_t;

typedef struct {
	double f_speed;
	double w_lenght;
	unsigned int migr_hbt:4;
}birds_t;

typedef struct {
	double weight;
	double height;
	char food[100];
}mammals_t;

typedef struct {
	double weight;
	double sw_depth;
	double salt_percentage;
}fish_t;

typedef union {
	insect_t insecto;
	birds_t birdo;
	mammals_t mammalo;
	fish_t fisho;
}classification;

typedef struct {
	char name[100];
	unsigned int type :3;
	classification class;
}fauna;

int choose_animal()
{
	unsigned key;
	printf("\nInsects: [0]\nBirds: [1] \nMammals: [2] \nFish: [3]\n");
	scanf("%u", &key);
	if (key >=0 && key <=3)
		return key;
	else 
		return -1;
}

fauna get_animal_type(fauna temp)
{
	int type;

	printf("\nPlease introduce the type of the animal.\n");
	type=choose_animal();

	if(type!=-1)
		temp.type=type;
	else
	{
		printf("\nError! Type must be a number between 0 and 3!\n");
		get_animal_type(temp);
	}
	return temp;
}

fauna get_animal_name(fauna temp)
{
	printf("Please introduce the name of the animal [name]: ");
	scanf("%100s", temp.name);
	return temp;
}

fauna read_insect (fauna temp)
{
	printf("Please introduce number of legs: ");
	scanf("%u",&temp.class.insecto.legs);

	printf("Please introduce life span [number]: ");
	scanf("%lf",&temp.class.insecto.life_span);

	return temp;
}

fauna read_bird (fauna temp)
{
	unsigned migr;

	printf("Please introduce the flying speed: ");
	scanf("%lf", &temp.class.birdo.f_speed);

	printf("Please introduce the wings lenght: ");
	scanf("%lf", &temp.class.birdo.w_lenght);

	printf("Please choose the migration habit.\nPermanent [0]; Short-distance [1]; Medium-distance [2]; Long-distance [3]; Other[4]: ");
	scanf("%u", &migr);

	if (migr >= 0 && migr <= 4)
		temp.class.birdo.migr_hbt=migr;
	else 
		temp.class.birdo.migr_hbt=4;

	return temp;
}

fauna read_mammal (fauna temp)
{
	printf("Please introduce weight: ");
	scanf("%lf", &temp.class.mammalo.weight);

	printf("Please introduce height: ");
	scanf("%lf", &temp.class.mammalo.height);

	printf("Please introduce the food: ");
	scanf("%100s", temp.class.mammalo.food);

	return temp;
}

fauna read_fish (fauna temp)
{
	printf("Please introduce weight: ");
	scanf("%lf", &temp.class.fisho.weight);

	printf("Please introduce the swimming depth: ");
	scanf ("%lf", &temp.class.fisho.sw_depth);

	printf("Please introduce the salt percentage: ");
	scanf("%lf", &temp.class.fisho.salt_percentage);

	if (temp.class.fisho.salt_percentage > 100)
		temp.class.fisho.salt_percentage = 100;

	if (temp.class.fisho.salt_percentage < 0)
		temp.class.fisho.salt_percentage = 0;

	return temp;
}

fauna readfauna ()
{
	fauna temp;

	temp=get_animal_type(temp);
	temp=get_animal_name(temp);

	switch (temp.type)
	{
		case insect:
			temp=read_insect(temp);
			break;
		case bird:
			temp=read_bird(temp);
			break;
		case mammal:
			temp=read_mammal(temp);
			break;
		case fish:
			temp=read_fish(temp);
			break;
	}

	return temp;
}

void display_insect(fauna temp)
{
	printf("Legs: %u\n", temp.class.insecto.legs);
	printf("Life span: %lf\n", temp.class.insecto.life_span );
}

void display_bird(fauna temp)
{
	printf("Flying speed: %lf\n",temp.class.birdo.f_speed);
	printf("Wings lenght: %lf\n", temp.class.birdo.w_lenght);
	printf("Migration habit: ");
	switch (temp.class.birdo.migr_hbt)
	{
		case permanent_t:
			printf("Permanent\n");
			break;
		case short_distance_t:
			printf("Short distance\n");
			break;
		case medium_distance_t:
			printf("Medium distance\n");
			break;
		case long_distance_t:
			printf("Long distance\n");
			break;
		case other_t:
			printf("Other, not specified\n");
			break;
	}
}

void display_mammal(fauna temp)
{
	printf("Weight: %lf\n", temp.class.mammalo.weight);
	printf("Height: %lf\n",temp.class.mammalo.height);
	printf("Food: %s\n", temp.class.mammalo.food);
}

void display_fish(fauna temp)
{
	printf("Weight: %lf\n", temp.class.fisho.weight);
	printf("Swimming depth: %lf\n", temp.class.fisho.sw_depth);
	printf("Salt percentage: %lf\n", temp.class.fisho.salt_percentage);
}

void display_one(fauna temp)
{
	printf("Name: %s\n", temp.name);
	switch (temp.type)
	{
		case insect:
			display_insect(temp);
			break;
		case bird:
			display_bird(temp);
			break;
		case mammal:
			display_mammal(temp);
			break;
		case fish:
			display_fish(temp);
			break;
	}
}

int show_menu()
{
	int key;

	printf("\nWhat would you like to do next?\n");
	printf("Add an entry [0]\n");
	printf("Delete an entry [1]\n");
	printf("Replace (edit) an entry [2]\n");
	printf("Lookup entries [3]\n");
	printf("Exit [4]\n");

	scanf("%d",&key);

	if (key >= 0 && key <= 3)
		return key;
	else 
		return -1;
}

void display_all(fauna database[], unsigned entries, unsigned key)
{
	unsigned contor=0;

	for (int i=1; i<=entries; i++)
		if (database[i].type==key)
		{
			printf("\n#%u\n", (contor++)+1);
			display_one(database[i]);
		}

	if (contor==0)
		printf("\nNothing here\n");
}

void lookupp(fauna *database, unsigned entries)
{

	unsigned key;

	printf("\nWhat would you like to lookup?\n");
	key=choose_animal();

	switch (key)
	{
		case insect:
		printf("\nInsects:\n");
		break;

		case bird:
		printf("\nBirds:\n");
		break;

		case mammal:
		printf("\nMammals:\n");
		break;

		case fish:
		printf("\nFish:\n");
		break;

		default:
		printf("\nWrong entry\n");
		lookupp(database, entries);
	}
	display_all(database, entries, key);
}

int choose_no(fauna *database, unsigned entries, unsigned type)
{
	unsigned no;

	display_all(database,entries,type);

	printf("Please choose the number: \n");
	scanf("%u",&no);

	if (no>entries)
		return -1;

	return no;
}

int verify_reg(fauna *database, unsigned entries, int type)
{
	int k=0;
	for (int i=1; i<=entries; i++)
	{
		if(database[i].type==type)
			k++;
	}
	return k;
}

int find_del(fauna *database, unsigned entries)
{
	int deleto=-1;
	unsigned contor=0;

	printf("\nWhat would you like to delete?\n");
	int type=choose_animal();

	if (verify_reg(database, entries, type) !=0)
		deleto=choose_no(database,entries,type);

	if (deleto !=-1)
		for (int i=1; i<=entries; i++)
		{
			if (database[i].type==type)
				contor++;
			if (contor==deleto)
				return i;
		}
	
	return -1;
}

int deletef(fauna *database, unsigned entries)
{
	int element=find_del(database,entries);

	if (element!=-1)
		for (int i=element; i<=entries; i++)
			database[i]=database[i+1];
	else
	{
		printf("\nNot a valid number!\n");
		return -1;
	}

	return 1;
}


fauna *replacen(fauna *database, unsigned entries)
{
	int x;
	int i;
	unsigned contor=0;

	printf("\nWhat would you like to replace?\n");
	int type=choose_animal();

	if (verify_reg(database,entries,type)!=0)
	{
		x=choose_no(database, entries, type);

		if (x>0)
		{
			for (i=1; i<=entries; i++)
			{
				if (database[i].type==type)
					contor++;
				if (contor==x)
					break;
			}
			if(contor==x)
				database[i]=readfauna(database[i]);
			else
				printf("\nNot enough entries.\n");
		}
		else
			printf("\nWrong number!\n");
	}
	else
		printf("\nNot enough entries!\n");

	return database;
}

void data()
{
	unsigned entries=1;
	fauna database[100];
	int getmove;

	printf("Welcome, please add an entry to the database to start.\n");
	database[entries]=readfauna(database[entries]);

	while (1)
	{
		getmove=show_menu();
		switch(getmove)
		{
			case add:
				entries++;
				database[entries]=readfauna(database[entries]);
				break;

			case lookup:
				lookupp(database, entries);
				break;

			case delete:
                if (entries!=0)
				{
					if (deletef(database, entries)!=-1)
                    	entries--;
                }
                else
                    printf("\nNothing to delete!\n");

				break;

			case replace:
				replacen(database, entries);
				break;

			case getout:
				exit(2);
		}
	}
}

int main ()
{
	data();

	return 0;
}
