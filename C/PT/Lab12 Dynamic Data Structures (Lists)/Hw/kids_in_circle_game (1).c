#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Please use distinct names or you cannot differentiate the kids in the list

typedef struct node
{
    char name[100];
    struct node *next;
    struct node *prev;
} node;

unsigned switcher=0;

void mem_error()
{
	printf("Could not allocate memory\n");
    exit(3);
}

void bad_input()
{
	printf("Bad input!\n");
	exit(4);
}

void add_to_list_here(node *root, char *here, char s[])
{
    node *add = (node *)malloc(sizeof(node));
    node *temp=root;

    if(!add)
	    mem_error();

    while (strcmp(temp->name,here)!=0)
        temp=temp->next;

    strcpy(add->name,s);

    temp->next->prev=add;
    add->next=temp->next;
    temp->next=add;
    add->prev=temp;

}

node *add_before(node *root, char *s)
{
    node *add = (node *)malloc(sizeof(node));

    if(!add)
	    mem_error();

    strcpy(add->name, s);

    root->prev->next=add;
    add->prev=root->prev;

    add->next=root;
    root->prev=add;

    root=add;

    return root;
}

void add_to_end(node *root, char *s)
{
    node *add = (node *)malloc(sizeof(node));
    node *temp=root;

    if(!add)
	    mem_error();

    do
    {
        temp=temp->next;
    }while(temp->next!=root);

    strcpy(add->name, s);

    add->prev=temp;
    temp->next=add;

    add->next=root;
    root->prev=add;

}


node* add_to_list(node *root, char *s)
{

    if (switcher == 0)
    {
        root->next=root;
        root->prev=root;
        strcpy(root->name, s);

        switcher=1;
    }

    else
    {
        node *temp;

        temp = root;

        do
        {
        	temp=temp->next;

            if ( (strcmp(s,temp->name) >= 0) && (strcmp(s,temp->next->name) <= 0) )  // if s->name is between 2 nodes
            {
                add_to_list_here(root,temp->name,s);
                break;
            }

            if (temp==root) //if it reaches here it means it's either before every node or after every node
            {
                if (strcmp(s,root->name)<=0)
                {
                    root=add_before(root, s);
                    break;
                }

                else
                {
                    add_to_end(root, s);
                    break;
                }
            }

        }while(1);

    }

    return root;
}

void print_list(node *root)
{
    node *temp = root;
    temp = root;

    do
    {
        printf("%s\n", temp->name);
        temp=temp->next;
    }
    while(temp!=root);

    printf("\n");
}

node *delete (node *root, char *s)
{
	node *prev = root;
	node *current=root;
	node *temp = root;

	while (strcmp(current->name,s)!=0)
	{
		prev=current;
		current=current->next;
	}

	if (current == root)
	{
		prev=current->prev;
		root=root->next;

		prev->next=root;
		root->prev=prev;
	}
	else if (current -> next == root)
	{
		prev->next=root;
		root->prev=prev;
	}
	else
	{
        temp=current->next;
		prev->next=temp;
		temp->prev=prev;
	}

	printf("Eliminating %s\n", current->name);
	free(current);
	return root;
}

void cc_wise (node *root, int n, unsigned total_kids)
{
	int i,j;
	node *temp = root;
	node *prev = temp->prev;
	char winner[100];

	while (temp->next!=root)
	{
		temp=temp->next;
		prev=temp->prev;
	}

	node *save=temp;

	for (i=1; i<total_kids; i++)
	{
		for (j=1; j<n; j++)
		{
			temp=temp->prev;
			prev=temp->prev;
			printf("Skipping %s\n", temp->next->name);
		}

		root=delete(root, temp->name);

		if (n!=1)
        	temp=prev;
        else
        {
        	save=save->prev;
        	temp=save;
        }

		printf("\n");
	}

	strcpy(winner,root->name);

	printf("Eliminating %s\n", root->name);
	free(root);

	printf("\nWinner: %s\nGame Over\n", winner);

	
}

void clock_wise (node *root, int n, unsigned total_kids)
{
	int i,j;
	node *temp = root;
	node *next = temp->next;
	char winner[100];

	for (i=1; i<total_kids; i++)
	{
		for (j=1; j<n; j++)
		{
			temp=temp->next;
			next=temp->next;
			printf("Skipping %s\n", temp->prev->name);
		}

		root=delete(root, temp->name);

		if (n!=1)
        	temp=next;
        else
        {
        	temp=root;
        }
        printf("\n");
	}

	strcpy(winner,root->name);

	printf("Eliminating %s\n", root->name);
	free(root);

	printf("\nWinner: %s\nGame Over\n", winner);
}

void game(node *root)
{
	int n;
	unsigned direction;
	node *count_kids=root;
	unsigned kids=1;

	do
	{
		kids++;
		count_kids=count_kids->next;
	}while (count_kids->next!=root);

	printf("%d\n", kids);
	printf("Please introduce n: ");
	
	if (scanf("%d", &n)==1)
	{
		if (n==0)
		{
			printf("You can't count to 0 in any direction.\n");
			exit(10);
		}
		printf("Now please introduce the direction\n");
		printf("If you want to go clock-wise please introduce 1.\n");
		printf("If you want to go counter-clockwise please introduce 2.\n");
		if (scanf("%u", &direction)==1)
			printf("Game start!\n");
		else
			bad_input();
	}
	else
		bad_input();

	if (n<0)
	{
		n=abs(n);
		direction++;
	}

	if (direction % 2 != 0)
	{
		printf("We are going clock-wise!\n");
		printf("Initial list:\n");
		print_list(root);
		clock_wise(root, n, kids);
	}
	else
	{
		printf("We are going counter-clockwise!\n");
		cc_wise(root,n,kids);
	}

}

int main(int argc, char*argv[])
{
	int i;
    unsigned long file_size;
    char *names;
    char *one_name;
    int count=0;

    if (argc!=2)
    {
        printf("Please give text name file in command line.\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1],"r");

    if (!fp)
    {
        printf("Could not open text file\n");
        exit(2);
    }

    fseek(fp, 0, SEEK_END);
    file_size= ftell(fp);
    rewind (fp);

    names = (char*)calloc(file_size+1,1);

    if (names==NULL)
    	mem_error();

    one_name = (char*)calloc(file_size+1,1);

    if (one_name==NULL)
	    mem_error();

    fread(names,1,file_size,fp);

    node *root = (node*)malloc(sizeof(node));

    if (!root)
	    mem_error();

    for (i=0; names[i]; i++)
    {
        if ((names[i]=='\n') || (names[i+1]==EOF))
        {
        	one_name[count]=0;
            count=0;

            if ((isspace((unsigned char)one_name[0])==0) && (one_name[0]!=0))
            	root=add_to_list(root, one_name);

            if (names[i+1]!=EOF)
          		memset(one_name,0,file_size);
        }
        else
            one_name[count++]=names[i];
    }

    if ((isspace((unsigned char)one_name[0])==0) && one_name[0]!=0)
    	root=add_to_list(root, one_name);

    printf("Initial list of kids:\n");
    print_list(root);

    game(root);



    fclose(fp);

    free(names);
    free(one_name);

    return 0;
}
