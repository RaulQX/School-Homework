#include <stdio.h>
#include <stdlib.h>

void bsrch(int left, int right)
{
	char key,comp;
	int middle = (left+right)/2;
	printf("Is your number: %d? [y/n]\n", middle);
	scanf("%c", &key);
	if (key == 'y')
	{
		printf("I found your number!\n");
		exit(1);
	}
	else
	{
		getchar();
		printf("How is your number compared to %d? [</>]\n", middle);
		scanf("%c", &comp);
		getchar();
		if (comp=='<')
			bsrch(left,middle-1);
		else if (comp == '>')
			bsrch(middle+1,right);
	}

}


int main ()
{

	bsrch(0,100);

	return 0;
}