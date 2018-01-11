/*
 * Utils.c
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */

#include <stdlib.h>
#include <string.h>

//This structure helps converting an integer to the book identifier string format

int getBookID(char* id)
{
	//Takes a string in the form of xxxx-xxxx and returns an int based on it.
	int tmp=0;
	int i=0;
	for (i=0;i<strlen(id);i++)
	{
		if ((id[i]-'0')<=9 && (id[i]-'0')>=0)
		{
			tmp=tmp*10+(id[i]-'0');
		}
	}

	return tmp;
}
char finalbuffer[33];
char* getBookIDS(int s)
{
	//Reverses the process above.
	char buffer[33];
	char buffer2[33];
	finalbuffer[0]=0;
	int firstHalf = s/10000;
	int secondHalf = s%10000;

	itoa(firstHalf,buffer,10);
	itoa(secondHalf,buffer2,10);
	strcat(finalbuffer,buffer);
	strcat(finalbuffer,"-");
	strcat(finalbuffer,buffer2);

	return finalbuffer;
}
