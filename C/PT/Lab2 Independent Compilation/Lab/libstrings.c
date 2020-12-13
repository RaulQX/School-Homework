#include <stdio.h>
//#include <string.h>

/* str1, str2 are the strings that are going to be compared in that order
   string_to is the string we are copying to
   string_from is the string we are copying from
   maxchars is the maximum number of characters we are copying
*/

/*int meincmp(char* str1, char* str2)
{
	return strcmp(str1,str2);
}

char * mystrcpy(char* string_to, char*string_from)
{
	return strcpy(string_to, string_from);
}

char * mystrncpy(char* string_to, char*string_from, int maxchars)
{
	return strncpy(string_to, string_from, maxchars);
}*/

int meinstrcmp (char* str1, char* str2)
{
	for (int i=0; str1[i]; i++)
	{
		if (str1[i]>str2[i])
			return 1;
		else if (str1[i]<str2[i])
			return -1;
	}
	int lenght1=0, lenght2=0;
	for (int i=0; str1[i]; i++)
		lenght1++;
	for (int i=0; str2[i]; i++)
		lenght2++;
	if (lenght1>lenght2)
		return 1;
	else if (lenght1<lenght2)
		return -1;
	else return 0;
}

char* mystrcpy (char* string_to, char* string_from)
{
	int i;
	for (i=0; string_from[i]; i++)
		string_to[i]=string_from[i];
	string_to[i]=0;
	return string_to;
}

char* mystrncpy (char* string_to, char* string_from, int maxlenght)
{
	int i;
	for (i=0; string_from[i] && i<maxlenght; i++)
		string_to[i]=string_from[i];
	string_to[i]=0;
	return string_to;
}