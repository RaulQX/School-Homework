#include <stdio.h>
#include <stdlib.h>

void error()
{
	printf("Error!\n");
	exit(2);
}

typedef struct node
{
	int key;
	struct node *next, *prev;
}node;

void init_list (node *start, int info)
{
	start->key=info;
	start->next=0;
	start->prev=0;
}

void show (node *start)
{
	node *p = (node*)malloc(sizeof(node*));

	if (!p)
		error();

	p=start;

	while (p!=0)
	{
		printf("%d ", p->key);
		p=p->next;
	}

	putchar('\n');
}

void add_node (node *start, int n)
{
	node *p = (node*)malloc(sizeof(node*));

	if (!p)
		error();

	node *q =start;

	p->key=n;

	while (q->next !=0)
		q=q->next;
	
	q->next=p;
	p->prev=q;
}

node* rev_list(node *start)
{	
	node *new_list = (node*)malloc(sizeof(node*));
	
	if (!new_list)
		error();
	
	node *q=start;

	while (q->next !=0)
		q=q->next;

	init_list(new_list, q->key);

	while (q->prev != 0)
	{	
		q=q->prev;
		add_node(new_list,q->key);
	}

	return new_list;
}

int main ()
{
	node *head= (node*)malloc(sizeof(node*));
	
	if (!head)
		error();
	
	node *revved_list;

	init_list(head, 0);
	
	for (int i=1; i<=35; i++)
		add_node(head,i);

	printf("Initial list:\n");
	show (head);

	revved_list=rev_list(head);

	printf("Reversed list:\n");
	show (revved_list);



	return 0;
}