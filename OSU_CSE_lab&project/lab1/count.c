#include<stdio.h>

int main( int number_of_args, char* list_of_args[] ) 
{
	int i;
	for (i = 0; i < number_of_args; i++) 
	{
		printf("%s", list_of_args[i]);
	}
}