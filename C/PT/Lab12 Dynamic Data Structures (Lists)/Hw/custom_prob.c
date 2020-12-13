/*
############################################################

Given a double linked list, swap the n-th node key from the
beginning with the n-th node from the end.

First node is node number 0.

If a swap cannot be made don't modify the list.

Examples:

List: 1 2 3 4 5
n=1
Output: 1 4 3 2 5

List: 1 2 3 4 5 6
n=3
Output: 1 2 4 3 5 6

############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEM 15

typedef struct node
{
	int key;
	struct node *next, *prev;
}node;

void error()
{
	printf("Error!\n");
	exit(2);
}

void initialize_list (node *root, int key)
{
	root->key = key;
	root->next=NULL;
	root->prev=NULL;
}

node* add_before_first_node (node *root, int key)
{
	node *adding=(node*)malloc(sizeof(node));

	if(!adding)
		error();

	initialize_list(adding,key);
	adding->next=root;
	root->prev=adding;
	root=adding;

	return root;
}

void print_list(node *root)
{
	node *temp=root;

	while (temp!=NULL)
	{
		printf("%d ", temp->key);
		temp=temp->next;
	}
	printf("\n");
}

void swapperino(node *head, unsigned n)
{
	node *temp_beginning=head;
	node *temp_ending=head;
	int aux;

	while (temp_ending->next !=NULL)
		temp_ending=temp_ending->next;

	for (int i=0; i<n; i++)
	{
		temp_beginning = temp_beginning->next;
		temp_ending = temp_ending->prev;
	}

	aux=temp_beginning->key;
	temp_beginning->key = temp_ending->key;
	temp_ending->key = aux;

}

int main ()
{
	node *root = (node*)malloc(sizeof(node));
	unsigned count=0;
	unsigned n;

	if (!root)
		error();

	initialize_list(root, MAX_ELEM);
	count++;

	for (int i=MAX_ELEM-1; i>=1; i--)
	{
		root=add_before_first_node(root, i);
		count++;
	}

	printf("Initial list:\n");
	print_list(root);

	printf("Please give n: \n");

	if ((scanf("%d",&n)==1) && n<count)
	{
		swapperino(root,n);
		printf("List after swapping the nodes:\n");
		print_list(root);
	}
	else
	{
		printf("Something didn't workout :(\nPlease try a different input\n");
		exit(3);
	}

	return 0;
}