#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
	double grade;
}	stud;

//n1=[l...m] = m-l+1;
//n2=[m+1...r] = r-(m+1)+1 = r-m

void merge_name (stud* v, int left, int middle, int right)
{

	int i, j, k;
	int n1= middle - left + 1;
	int n2= right - middle;

	stud leftvect[n1], rightvect[n2];

	for (i=0; i<n1; i++)
	{
		strcpy(leftvect[i].name, v[left+i].name);
		leftvect[i].grade = v[left+i].grade;
	}
	for (i=0; i<n2; i++)
	{
		strcpy(rightvect[i].name, v[i+middle+1].name);
		rightvect[i].grade = v[i+middle+1].grade;
	}

	i=0;
	j=0;
	k=left;

	while (i<n1 && j<n2)
	{
		if(strcmp(leftvect[i].name, rightvect[j].name) <= 0)
		{
			strcpy(v[k].name, leftvect[i].name);
			v[k].grade = leftvect[i].grade;
			i++;
		}
		else
		{
			strcpy(v[k].name, rightvect[j].name);
			v[k].grade = rightvect[j].grade;
			j++;
		}
		k++;
	}

	while (i<n1)
	{
		strcpy(v[k].name, leftvect[i].name);
		v[k].grade = leftvect[i].grade;
		i++;
		k++;
	}

	while (j<n2)
	{
		strcpy(v[k].name, rightvect[j].name);
		v[k].grade = rightvect[j].grade;
		j++;
		k++;
	}
}

void mergesort_name(stud *v, int l, int r)
{
	if (l<r)
	{
		int m=(l+r)/2;

		mergesort_name(v, l, m);    //left part
		mergesort_name(v, m+1, r);  //right part

		merge_name (v, l, m, r);
	}
}

void merge_grades (stud* v, int left, int middle, int right)
{

	int i, j, k;
	int n1= middle - left + 1;
	int n2= right - middle;

	stud leftvect[n1], rightvect[n2];

	for (i=0; i<n1; i++)
	{
		strcpy(leftvect[i].name, v[left+i].name);
		leftvect[i].grade =v [left+i].grade;
	}
	for (i=0; i<n2; i++)
	{
		strcpy(rightvect[i].name, v[i+middle+1].name);
		rightvect[i].grade = v[i+middle+1].grade;
	}

	i=0;
	j=0;
	k=left;

	while (i<n1 && j<n2)
	{
		if(leftvect[i].grade > rightvect[j].grade)
		{
			strcpy(v[k].name, leftvect[i].name);
			v[k].grade = leftvect[i].grade;
			i++;
		}
		else
		{
			strcpy(v[k].name, rightvect[j].name);
			v[k].grade = rightvect[j].grade;
			j++;
		}
		k++;
	}

	while (i<n1)
	{
		strcpy(v[k].name, leftvect[i].name);
		v[k].grade = leftvect[i].grade;
		i++;
		k++;
	}

	while (j<n2)
	{
		strcpy(v[k].name, rightvect[j].name);
		v[k].grade = rightvect[j].grade;
		j++;
		k++;
	}
}

void mergesort_grades(stud *v, int l, int r)
{
	if (l<r)
	{
		int m=(l+r)/2;

		mergesort_grades(v, l, m);   
		mergesort_grades(v, m+1, r);

		merge_grades (v, l, m, r);
	}
}

void show_menu ()
{
	printf("Please introduce a number:\n\n");
	printf("0: Exit program;\n");
	printf("1: Give N, number of students;\n");
	printf("2: Enter the students;\n");
	printf("3: Display class in alphabetic order;\n");
	printf("4: Display class creating a top based on grades;\n");
	printf("5: Display the first 3 students according to their grade.\n");
	putchar('\n');
}

void menu()
{
	int n;
	int key;
	stud students[100];

	while (1)
	{
		show_menu();
		scanf("%d", &key);
		putchar('\n');

		switch (key)
		{
			case 0: 
				exit(1);

			case 1:
				printf("Please introduce the number of students: ");
				scanf("%d", &n);
				getchar();
				putchar('\n');
				break;

			case 2:
				printf("Format: [name] [grade]\n\n");
				for (int i=0; i < n; i++)
				{
					scanf("%100s %lf", students[i].name, &students[i].grade);
					getchar();
				}
				break;

			case 3:
				mergesort_name(students, 0, n);
				for (int i=1 ; i <= n ; i++)
					printf("%d: %s %lf\n", i, students[i].name, students[i].grade);
				break;

			case 4:
				mergesort_grades(students, 0, n);
				for (int i=0 ; i < n ; i++)
					printf("%d: %s %lf\n", i+1, students[i].name, students[i].grade);
				break;

			case 5:
				if (n>=3)
				{
					mergesort_grades(students, 0, n);
					for (int i=0 ; i < 3 ; i++)
						printf("%d: %s %lf\n", i+1, students[i].name, students[i].grade);
				}
				else
					printf("!!!Please introduce at least 3 students.\n\n");
				break;
		}
	}
}


int main ()
{
	menu();

	return 0;
}
