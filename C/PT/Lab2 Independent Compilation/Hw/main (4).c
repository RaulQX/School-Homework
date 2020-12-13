#include "cstrings.h"
#include <stdio.h>

typedef unsigned long size_t;

int main ()
{
	char s1[50]="Ala_";
	char s2[50]="balla";
	char s3[50]="proton";
	char s4[50];
	char s5[50];

	mystrcpy(s5,s1);

	printf("mystrcat of %s & %s: %s\n",s5, s2, mystrcat(s1,s2));
	printf("strcpy of %s: %s\n", s3, mystrcpy(s4,s3));
	printf("strcmp of: %s and %s: %d\n", s1, s4, mystrcmp(s1,s4));

	return 0;
}