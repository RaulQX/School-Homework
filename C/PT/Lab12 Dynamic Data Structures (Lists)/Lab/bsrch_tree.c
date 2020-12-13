#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 0.001


void error()
{
	printf("Error!\n");
	exit(2);
}

typedef struct btnode
{
	double info;
	struct btnode *left, *right;
}btnode;

void pre_order(struct btnode* node) 
{ 
	if (node == NULL) 
		return; 

	printf("%lf ", node->info);   

	pre_order(node->left);   

	pre_order(node->right); 
}  

btnode * makenode (double info)
{
	btnode *new=(btnode*)malloc(sizeof(btnode*));

	if (!new)
		error();

	new -> info = info;

	new->left=NULL;
	new->right=NULL;

	return new;
}

btnode* add_to_tree(double info, btnode *node)
{

	if (node == NULL)
		return makenode(info);


	if (fabs(info - (node -> info))>eps)
	{	
		if (info < node-> info)
			node -> left = add_to_tree(info, node -> left);
		else 
			node -> right = add_to_tree(info, node -> right);
	}

	return node;
}

btnode * makebtr()
{
	btnode *root = (btnode*)malloc(sizeof(btnode*));

	if (!root)
		error();

	double info;

	printf("Please introduce the root: \n");
	scanf("%lf", &info);

	root=makenode(info);
	
	printf("Now please introduce the other values\nIf you want to stop introduce a character.\n");

	while (1)
	{
		if (scanf("%lf",&info)==0)
			break;
		else
		{
			add_to_tree(info, root);
		}

	}

	return root;
}

void menu ()
{
	btnode *root=makebtr();

	printf("Binary tree in preorder:\n");
	pre_order(root);

	putchar('\n');
}


int main ()
{
	menu();

	return 0;
}