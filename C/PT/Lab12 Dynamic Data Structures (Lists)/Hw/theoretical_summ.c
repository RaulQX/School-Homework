#include <stdio.h>
#include <stdlib.h>
#define searchedKey 10

struct btsnode
{
	int key;
	struct btsnode *left, *right;
};

struct lnode
{
	int key;
	struct lnode *next;
};

int main ()
{
	struct lnode *root,*crt;
	struct btsnode *rootbt;

	root=(struct lnode*)malloc(sizeof(struct lnode));
	if (!root)
	{
		printf("Error\n");
		exit(2);
	}

	root->key=10;
	root->next=NULL;
	crt=root;

	while (crt != NULL)
	{
		if (crt -> key == searchedKey)
		{
			printf("Found!\n");
			break;
		}
		else
			crt=crt->next;

	}
	
	free(root);

	rootbt=(struct btsnode*)malloc(sizeof(struct btsnode));
	if (!rootbt)
	{
		printf("Error!\n");
		exit(2);
	}
	rootbt->key=30;
	rootbt->left=NULL;
	rootbt->right=NULL;

	printf("Root key: %d\n", rootbt->key);

	free(rootbt);

	return 0;
}