#include <stdio.h>
#include <stdlib.h>

void error()
{
	printf("Error!\n");
	exit(2);
}

typedef struct node_s
{
	int info;
	struct node_s *next;
}node_s;

typedef struct node_d
{
	int info;
	struct node_d *prev,*next;
}node_d;

void init_s(node_s *head, int n)
{
	head->info=n;
	head->next=0;
}

void init_d(node_d *head, int n)
{
	head->info=n;
	head->next=0;
	head->prev=0;
}

void add_s(node_s *head, int n)
{
	node_s *add=(node_s*)malloc (sizeof(node_s*));

	if(!add)
		error();

	node_s *temp=head;

	add->info=n;

	while (temp->next!=0)
		temp=temp->next;

	temp->next=add;
	add->next=0;
}

void add_d(node_d *head, int n)
{
	node_d *add=(node_d*)malloc (sizeof(node_d*));

	if(!add)
		error();
	
	node_d *temp=head;

	add->info=n;

	while (temp->next!=0)
		temp=temp->next;

	temp->next=add;
	add->prev=temp;
	add->next=0;
}

void show_s(node_s *head)
{
	node_s *temp=(node_s*)malloc (sizeof(node_s*));
	temp=head;
	while (temp!=0)
	{
		printf("%d ", temp->info);
		temp=temp->next;
	}
	putchar('\n');
}

void show_d(node_d *head)
{
	node_d *temp=(node_d*)malloc (sizeof(node_d*));

	if(!temp)
		error();
	
	temp=head;
	while (temp!=0)
	{
		printf("%d ", temp->info);
		temp=temp->next;
	}
	putchar('\n');
}

void split (node_s *simp_list, node_d *f_list, node_d *s_list, int key)
{
	node_s *temp=(node_s*)malloc (sizeof(node_s*));

	if(!temp)
		error();

	temp=simp_list;

	init_d(f_list, simp_list->info);

	while (temp->info!=key)
	{
		if (temp->next==0)
		{
			printf("Key is too big!\n");
			exit(2);
		}
		else
		{
			temp=temp->next;
			add_d(f_list,temp->info);
		}
	}

    if(temp->next!=0)
    {
        init_d(s_list, temp->next->info);

        temp=temp->next->next;

        while (temp!=0)
        {
            add_d(s_list,temp->info);
            temp=temp->next;
        }
    }
    else
    {
    	printf("Not enough elements to create a second list!\n");
    	exit(3);
    }
}

int main ()
{
	int key=20;

	node_s *head = (node_s*)malloc (sizeof(node_s*));
	if (!head)
		error();
	node_d *first_part = (node_d*)malloc (sizeof(node_d*));
	if (!first_part)
		error();
	node_d *second_part = (node_d*)malloc (sizeof(node_d*));
	if (!second_part)
		error();

	init_s(head, 0);

	for (int i=1; i<=30; i++)
		add_s(head ,i);

	printf("Initial list:\n");
	show_s(head);

	split(head, first_part, second_part, key);

	printf("First list:\n");
	show_d(first_part);

	printf("Second list:\n");
	show_d(second_part);

	return 0;
}
