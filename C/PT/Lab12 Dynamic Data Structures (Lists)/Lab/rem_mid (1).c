#include <stdio.h>
#include <stdlib.h>

void error()
{
	printf("Error!\n");
	exit(2);
}

typedef struct node
{
	int info;
	struct node *next;

}node;


void init_list(node *start, int n)
{
	start -> info = n;
	start ->next = start;
}

void print_list (node *start)
{
	node *temp=start;

	do
	{
		printf("%d ", temp->info);
		temp=temp->next;
	}while(temp!=start);

	putchar('\n');
}

void add_list(int n, node* start)
{
	node *adding = (node *)malloc(sizeof(node*));

	if (!adding)
		error();

	node *temp = start;
	while (temp -> next != start)
		temp=temp->next;

	adding -> info = n;

	temp -> next = adding;
	adding -> next = start;
}

void remove_middle (node * start)
{
	int contor=0;
	node *temp=start;
	node *prev;
	
	do
	{
		contor++;
		temp=temp->next;
	}while(temp!=start);

	if (contor!=1)
	{
		for (int i=0; i<contor/2-1; i++)
			temp=temp->next;

		prev=temp;
		temp=temp->next;
		prev->next=prev->next->next;

		free(temp);
	}
	else
	{
		free(start);
		printf("List does not contain any elements!\n");
		exit(3);
	}
	
}


int main ()
{
	node *start = (node*)malloc(sizeof(node*));
	
	if (!start)
		error();
	else
		init_list(start, 0);

	for (int i=1; i<=10; i++)
		add_list(i, start);

	printf("List before:\n");
	print_list(start);

	printf("List after:\n");
	remove_middle(start);
	print_list(start);

	return 0;
}