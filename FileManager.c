/*
 * FileManager.c
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */
#include "FileManagerInterface.h"
//This data structure helps to save and load data from a external file
void proceedWriteData(Controller* contr,FILE* fil)
{
	//Dumps the linked list into a file with each of the book's fields on a separate line. First line represents the number of books
	int actualWorkingSize = controllerGetSize(contr);
	int tmpSize=0;
	LinearNode* base = controllerGetAll(contr,&tmpSize);
	fprintf(fil,"%d\n",actualWorkingSize);
	int i=0;

	for (i=0;i<actualWorkingSize;i++)
	{
		fprintf(fil,"%s\n%s\n%s\n%d\n%d\n%s\n%d\n",getBookIDS(base->id),bookgetAuthor(base->elem),bookgetName(base->elem),bookgetYear(base->elem),bookgetPrice(base->elem),bookIsLoaned(base->elem)==1?"Yes":"No",bookgetLoanCount(base->elem));

		if (bookIsLoaned(base->elem))
		{
			fprintf(fil,"%s\n",bookGetCustomer(base->elem));
		}
		base = base->next;

	}
}
void repairString(char * f)
{
	//FGETS stores a \n after the string itself, which we want to remove because it doesn't work otherwise.
	int g = strlen(f);
	int i=0;
	for (i=0;i<g;i++)
	{
		if (f[i]=='\n')
		{
			f[i]='\0';
		}
	}
}
void proceedReadData(Controller* contr,FILE* fil)
{
	//Reverses the write process and adds each read book in the linkedlist with the help of the controller.
	int size=0;
	fscanf(fil,"%d ",&size);
	char bookID[20];
	char bookAuthor[20];
	char bookName[20];
	int bookYear=0;
	int bookPrice=0;
	bool isLoaned=false;
	int bookLoanCount=0;
	char bookCustomer[20];

	char tmpBuffer[20];
	int i=0;
	for (i=0;i<size;i++)
	{
		//fgetc(fil);
		fgets(bookID,20,fil);
		repairString(bookID);
		fgets(bookAuthor,20,fil);
		repairString(bookAuthor);
		fgets(bookName,20,fil);
		repairString(bookName);
		fscanf(fil,"%d ",&bookYear);
		fscanf(fil,"%d ",&bookPrice);
		//fgetc(fil);
		fgets(tmpBuffer,20,fil);
		repairString(tmpBuffer);
		if (strcmp(tmpBuffer,"Yes")==0)
		{
			isLoaned=true;
		}
		else
		{
			isLoaned=false;
		}
		fscanf(fil,"%d ",&bookLoanCount);
		if (isLoaned)
		{
			fgets(bookCustomer,20,fil);
			repairString(bookCustomer);
		}
		///////////////////
		Book* buc1 = (Book*)malloc(sizeof(Book));
		Book_init(buc1, bookName,bookAuthor,bookYear,bookPrice);
		bookSetLoanCount(buc1,bookLoanCount);
		if (isLoaned)
		{
			bookSetLoaned(buc1,true);
			bookSetCustomer(buc1,bookCustomer);
		}
		else
		{
			bookSetLoaned(buc1,false);
		}
		controllerAdd(contr,getBookID(bookID),buc1);
		Book_destroy(buc1);
		free(buc1);
		///////////////////
	}
}

void writeData(Controller* contr)
{
	//Opening the file,handling errors, writing data to the file
	 FILE * pFile;
	 pFile = fopen ("book.dat","w");
	 if (pFile!=NULL)
	 {
		 proceedWriteData(contr,pFile);
		 printf("Books have been successfully written to the disk.\n");
	 }
	 else
	 {
		 printf("There was an unexpected error while saving the books.\n");
	 }
	 fclose(pFile);

}
void readData(Controller* contr)
{
	//Opening the file,handling errors, reading data from the file
	 FILE * pFile;
	 pFile = fopen ("book.dat","r");
	 if (pFile!=NULL)
	 {
		 proceedReadData(contr,pFile);
		 printf("Books have been successfully read from the disk.\n");
	 }
	 else
	 {
		 printf("There are no books stored on the disk. You'll have to enter them manually and exist accordingly to save them.\n");
	 }
	 fclose(pFile);
}
