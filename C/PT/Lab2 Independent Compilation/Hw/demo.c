#include "cstrings.h"
#include <stdio.h>



int main ()
{
	char s[100]="This is an example string for using mystrlen of lenght:";
	char s2[100]="This is another example string ";
	char s3[100];
	char s4[100]="Concatenate me to: ";
	char s5[100]="To this but not all of me.";
	char s6[100]="We search for s...";
	char s7[100]="We search for h...";
	char s8[100]="Duplicate me please!";
	char s9[100];
	char s10[100]="Copy until here even though it goes on longer";
	char s11[100];
	char s12[50]="eXaMpLe";

	int n=15;

	printf("%s %lu\n", s, mystrlen(s));
	printf("If we want to see the lenght of the strings but maximum n characters we can use mystrnlen: %lu\n", mystrnlen(s,n));
	printf("If we want to search for a character c (e) in a n (15) bytes we can use mymemchr: %s\n", (char*)mymemchr(s2,'e',n));
	printf("If we want to compare n bytes of memory of 2 strings, s1 and s2 we can use mymemcmp: %d\n", mymemcmp(s,s2,n));
	printf("If we want to copy n bytes of memory we can use mymemcpy: %s\n", (char*)mymemcpy(s3,s2,n));
	printf("If we want to set n byes of memory to c(e) we can use mymemset: %s\n", (char*)mymemset(s2,'e',n));
	printf("If we want to concatenate 2 strings we can use mystrcat: %s\n", mystrcat(s4,s2));
	printf("If we want to concatenate n bytes from the second string we can use mystrncat: %s\n", mystrncat(s4,s5,n));
	printf("If we want to search for a character (s) in a string terminated with \\0 mystrchr: %s\n", mystrchr(s6, 's'));
	printf("If we want to search for a character (h) in a string terminated with \\0 from the right mystrrchr:  %s\n", mystrrchr(s7, 'h'));
	printf("If we want to compare 2 strings we can use mystrcmp: %d\n", mystrcmp(s6,s7));
	printf("If we want to compare at maximum n(3) chars from a string we can use mystrncmp: %d\n", mystrncmp(s6,s7,3));
	printf("If we want to search for a string in another string we can use mystrstr: %s\n", mystrstr(s6, "for"));
	printf("If we want to find the span of a string in another string we can use mystrspn: %lu\n", mystrspn(s6,"We sr"));
	printf("If we want to find the span of of a string until we find the chars we can use mystrcspn: %lu\n", mystrcspn(s6,"."));
	printf("If we want to search for multiple chars in a string we can use mystrpbrk: %s\n", mystrpbrk(s6,"f."));
	printf("If we want to duplicate a string we can use mystrdup: %s\n", mystrdup(s8));
	printf("If we want to duplicate a string with maximum n(4) chars we can use mystrndup: %s\n", mystrndup(s8,4));
	printf("If we want to copy a string into another string we can use mystrcpy: %s\n", mystrcpy(s9,s2));
	printf("If we want to copy a string of maximum n chars into another string we can use mystrncpy: %s\n", mystrncpy(s11,s10,n));
	printf("If we want to use uppercase characters we can use strtoupper: %s\n", strtoupper(s12));
	printf("If we want to use lowercase characters we can use strtolower: %s\n", strtolower(s12));
	
	return 0;

}