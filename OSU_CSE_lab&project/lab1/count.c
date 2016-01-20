#include<stdio.h>

/*
Write a program in C called “count” to read a text file and print the following statistics on the screen as
well to an output file:
the size of the file in bytes
number of times the search-string specified in the second argument appeared in the file
*/
int compare(char *str, char *target);
int main( int number_of_args, char* list_of_args[] ) 
{
	static const STRLEN = 1000;

	char str[STRLEN];
	int count = 0;
	int size = 0;
	if ( number_of_args != 4 )
	{
		printf("you are supposed to provide 3 arguments for input file, search string and output file.\n");
		exit(-1);
	}
	FILE *fin = fopen( list_of_args[1], "r" );
	FILE *fout = fopen( list_of_args[3], "w" );
	char *target = list_of_args[2];
	if (!fin) {
		printf("the first file is invalid\n");
		exit(-1);
	}
	if (!fout) {
		printf("the second file is invalid\n");
		exit(-1);
	}
	
	while(fgets(str, STRLEN, fin))
	{
		if(strlen(str) == 1)
		{
			fgets(str, STRLEN, fin);
			// printf("sss");
			continue;
		} 
		int c, len = strlen(target);
		// printf("%s%d", str, strlen(str));
		c = compare(str, target);
		// printf("c = %d\n", count);
		count += c;
		// if(str[strlen(str)-1] == EOF) {
		// 	printf("%s", str);
		// 	break;}
		if(c == 0 && strlen(str) == STRLEN) {fseek(fin, -len, SEEK_CUR);printf("ddddd");}
		// fgets(str, STRLEN, fin);
	}
	size = ftell(fin);
	fprintf(fout, "Size of file is %d\nNumber of matches = %d\n", size, count);
}

int compare(char *str, char *target)
{
	int count = 0, i = 0, j = 0;
	for(i = 0; i < strlen(str); i++)
	{
		for(j = 0; j < strlen(target) && i+j < strlen(str); j++)
		{
			if(str[i+j] != target[j])
			{
				break;
			}
		}
		if(j == strlen(target))
		{
			count++;
		}
	}
	printf("c = %d\n", count);
	return count;
}