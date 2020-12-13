#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>

typedef unsigned long size_t;

//1
size_t mystrlen(char*s)
{
	size_t lenght=0;

	for (size_t i=0; s[i]; i++)
		lenght++;

	return lenght;
}


//2
size_t mystrnlen(char*s, size_t maxlenght)
{
	size_t lenght=0;

	for (size_t i=0; s[i] && i<maxlenght; i++)
		lenght++;

	return lenght;
}

//3
void * mymemchr(void  *str, int character, size_t maxlenght)
{
	char* string = (char*)str;
	size_t i=0;

	while (maxlenght--)
	{
		if(string[i] == (char)character)
			return string+i;
		i++;
	}

	return NULL;
}

//4
int mymemcmp (const void* str1, const void* str2, size_t maxmem)
{
	char*s1=(char*)str1;
	char*s2=(char*)str2;
	size_t i=0;

	while (maxmem--)
	{	if (s1[i]!=s2[i])
			return s1[i]-s2[i];
		i++;
	}

	return 0;
}

//5
void *mymemcpy(void *string_to, const void *string_from, size_t maxmem)
{
	//Memory areas must not overlap as in man description//

	char *s1 = (char*)string_to;
	char *s2 = (char*)string_from;
	size_t i=0;

	while (maxmem--)
	{
		s1[i]=s2[i];
		i++;
	}

	return string_to;
}

//6
void *mymemset(void *str, int character, size_t n)
{
	char *s=(char*)str;

	for (size_t i=0; i<n; i++)
		s[i]=character;

	return s;
}

//7
char* mystrcat(char* string_to, char* string_from)
{
	size_t i;
	size_t appending_point=mystrlen(string_to);
	size_t maxlen=mystrlen(string_from);

	for (i=0; i<maxlen; i++)
		string_to[appending_point+i]=string_from[i];
	
	string_to[appending_point+i]=0;
	
	return string_to;
}

//8
char* mystrncat(char* string_to, char* string_from, size_t n)
{
	size_t i;
	size_t appending_point=mystrlen(string_to);
	size_t maxlen=mystrlen(string_from);

	for (i=0; i<maxlen && i<n; i++)
		string_to[appending_point+i]=string_from[i];

	string_to[appending_point+i]=0;
	
	return string_to;
}

//9
char *mystrchr (char* str, int c)
{
	for (size_t i=0; str[i]; i++)
		if (str[i] == (unsigned char) c)
			return str+i;

	return NULL;
}

//10
char *mystrrchr (char* str, int c)
{
	size_t lenght = mystrlen(str)-1;

	for (size_t i = lenght; i>=0; i--)
		if (str[i] == (unsigned char) c)
			return str+i;
	return NULL;
}

//11
int mystrcmp(char *str1, char* str2)
{
	for (int i=0; str1[i] && str2[i]; i++)
		if (str1[i]!=str2[i])
			return str1[i]-str2[i];

	int lenght1=mystrlen(str1);
	int lenght2=mystrlen(str2);

	if (lenght1==lenght2)
		return 0;
	else if (lenght1>lenght2)
		return 1;
	else return -1;
}

//12
int mystrncmp(char *str1, char* str2, size_t n)
{
	size_t i;

	for (i=0; str1[i] && str2[i] && i<n; i++)
		if (str1[i]!=str2[i])
			return str1[i]-str2[i];

	if (i==n)
		return 0;
	else
	{
		int lenght1=mystrlen(str1);
		int lenght2=mystrlen(str2);
	if (lenght1==lenght2)
		return 0;
	else if (lenght1>lenght2)
		return 1;
	else return -1;
	}
}

//13
size_t mystrspn (char *str, char* characters)
{
	size_t bytes=0, i, j;

	for (i=0; str[i]; i++)
	{
		for (j=0; characters[j]; j++)
			if (str[i] == characters[j])
			{	
				bytes++;
				break;
			}
		if (characters[j]==0)
			return bytes;
	}

	return bytes;
}

//14
size_t mystrcspn(char*str1, char* chars)
{
	size_t i,j;

	for (i=0; str1[i]; i++)
	{
		for (j=0; chars[j]; j++)
		{
			if (str1[i]==chars[j])
				return i;
		}
	}

	return i;
}

//15
char *mystrstr(char*str, char*baby_str)
{
	size_t i,j,k;

	for (i=0; str[i]; i++)
		if (str[i]==baby_str[0])
		{
			for(j=0, k=i; baby_str[j] && str[k]; j++, k++)
				if (str[k]!=baby_str[j])
					break;

			if (baby_str[j]==0)
				return str+i;
		}

	return NULL;
}

//16
char* mystrpbrk(char*str, char*chars)
{
	for (size_t i=0; str[i]; i++)
	{
		for (size_t j=0; chars[j]; j++)
		{
			if(str[i]==chars[j])
				return str+i;
		}
	}

	return NULL;
}

//17
char *mystrdup(char*string_to)
{
	size_t len=mystrlen(string_to);
	char *sdup=malloc(len);

	if (sdup)
		mymemcpy(sdup,string_to,len);
	else return NULL;

	return sdup;
}

//18
char *mystrndup(char*string_to, size_t bytes)
{

	char *sdup=malloc(bytes+1);

	if (sdup)
		mymemcpy(sdup,string_to,bytes);
	else return NULL;

	return sdup;
}

//19
char* mystrcpy(char*string_to, char*string_from)
{
	size_t i;

	for (i=0; string_from[i]; i++)
		string_to[i] = string_from[i];

	string_to[i] = 0;

	return string_to;
}

//20
char *mystrncpy(char *string_to, char*string_from, size_t n)
{
	size_t i;

	for (i=0; i<n && string_from[i]; i++)
		string_to[i]=string_from[i];

	while (i<n)
		string_to[i++]=0;

	return string_to;
}

char *strtoupper(char *str)
{
	size_t i;

	for (i=0; str[i]; i++)
		if (str[i]>='a' && str[i]<='z')
			str[i]=str[i]-('a'-'A');

	return str;
}

char *strtolower(char *str)
{
	size_t i;

	for (i=0; str[i]; i++)
		if (str[i]>='A' && str[i]<='Z')
			str[i]=str[i]+('a'-'A');

	return str;
}