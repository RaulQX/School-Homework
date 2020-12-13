#include "libstrings.h"
#include <stdio.h>

int main ()
{
	char s1[50]="Alabala_Protocala";
	char s2[50]="Nabla_babla_Monocala";
	char s3[50], s4[50];
	int n=8;
	int cmp;

	cmp=meinstrcmp(s1,s2);
	mystrcpy(s3,s2);
	mystrncpy(s4,s2,n);

	printf("strcmp: %d\n", cmp);
	printf("strcpy: %s\n", s3);
	printf("strncpy: %s\n", s4);

	return 0;
}