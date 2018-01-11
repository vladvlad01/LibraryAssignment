/*
 * linearlist.c
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */

#include <stdio.h>
#include <stdlib.h>

#include "BookInterface.h"
#include "ControllerInterface.h"
#include "FileManagerInterface.h"
#include "LinearListInterface.h"

//This is the main file that operates the entire application

//Declaring the structures templates
void runUI();
void menu();
void addNewBook();
void takeOutBook();
void returnBook();
void deleteOldBook();
void viewAllBooks();
void specificBook();
void popular();
void priceSearch();
int getBookIdentifier();
Controller *contr;
LinearList *repo;

//Main function
void main()
{
	//output stream buffer size set to 0 - this helps me to run the code using Eclipse IDE
	setvbuf(stdout, NULL, _IONBF, 0);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	runUI(); //initializing the application by calling the user interface function
}
//Creating the linear list and the controller
void runUI()
{
	repo = linearlistInit(); //creating the LinearList
	contr = controllerInit(repo);
	menu();
}

int readNumber()
{
	int cmd = 0;
	scanf("%d", &cmd);
	return cmd;
}
//main menu
void menu()
{
	int choice;
	readData(contr);
	do
	{
		printf("\nLibrary Menu\n\n");
		printf("1. Add a new Book\n");
		printf("2. Take out a book  \n");
		printf("3. Return a book \n");
		printf("4. Delete an old book \n");
		printf("5. View all books\n");
		printf("6. View a specific book\n");
		printf("7. View details of most popular and least popular books\n");
		printf("8. Price search\n");
		printf("9. Exit\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: addNewBook();
		break;
		case 2: takeOutBook();
		break;
		case 3: returnBook();
		break;
		case 4: deleteOldBook();
		break;
		case 5: viewAllBooks();
		break;
		case 6: specificBook();
		break;
		case 7: popular();
		break;
		case 8: priceSearch();
		break;
		case 9:
			break;
		default: printf("\nInvalid choice!\n");
		break;
		}

	} while (choice != 9);
	writeData(contr);
}
//Adding a book to the list
void addNewBook()
{
	if (controllerGetSize(contr)==10)
	{
		printf("The list is full. You cannot add any more books.\n");
	}
	else
	{
		int year = 0;
		printf("Enter the detail of book \n");
		int convertedID = getBookIdentifier();

		char name[20];
		printf("Enter book name: ");
		getchar();
		gets(name);

		char author[20];
		printf("Enter book author: ");
		gets(author);

		do
		{
			printf("Please keep in mind that the year of publication can not bee older than 2008: ");
			year = readNumber();
		}while(year<2007);

		printf("Enter price of the book: ");
		int price = readNumber();

		Book* tmp = (Book*)malloc(sizeof(Book));
		Book_init(tmp,name,author,year,price);
		if (controllerAdd(contr,convertedID,tmp)==true)
		{
			printf("Adding was successful.\n");
		}
		else
		{
			printf("Adding failed.\n");
		}
	}
}
//Using a boolean flag a book becomes unavailable to rent
void takeOutBook()
{
	printf("Enter the detail of book to be returned \n");
	int convertedID = getBookIdentifier();
	char customer[20];
	printf("Enter customer name: ");
	getchar();
	gets(customer);
	if (controllerLoanBook(contr,convertedID,customer)==true)
	{
		printf("Loaning successful.\n");
	}
	else
	{
		printf("Loaning failed. The book doesn't exist or is already loaned.\n");
	}
}
//Using a boolean flag a book becomes available for rent
void returnBook()
{
	printf("Enter the detail of book to be returned \n");
	int convertedID = getBookIdentifier();
	if (controllerReturnBook(contr,convertedID)==true)
	{
		printf("Return successful.\n");
	}
	else
	{
		printf("Return failed. The book doesn't exist or is not loaned.\n");
	}
}
//Removes a book from the list by ID, calling a method that will free the book name from memory
void deleteOldBook()
{
	printf("Enter the book ID you want to delete:\n");
	int convertedID = getBookIdentifier();
	Book* requested = controllerGetById(contr,convertedID);
	if (bookgetYear(requested)>=2010)
	{
		if (controllerRemove(contr,convertedID)==true)
		{
			printf("Book removal was successful.\n");
		}
		else
		{
			printf("Book removal failed. Does not exist in the database.\n");
		}
	}
	else
	{
		printf("Only books older than 2010 can be deleted.\n");
	}
}
//Shows all book using controllerGetAll method
void viewAllBooks()
{
	int size = controllerGetSize(contr);
	if (size!=0)
	{
		int tmpSize = 0;
		LinearNode* base = controllerGetAll(contr,&tmpSize);
		printf("The available books are:\n");
		int i=0;
		for (i=0;i<size;i++)
		{
			printf("ID: %s - Author: %s - Name: %s - Year: %d - Price: %d - Loaned: %s - LoanCount: %d",getBookIDS(base->id),bookgetAuthor(base->elem),bookgetName(base->elem),bookgetYear(base->elem),bookgetPrice(base->elem),bookIsLoaned(base->elem)==1?"Yes":"No",bookgetLoanCount(base->elem));
			if (bookIsLoaned(base->elem))
			{
				printf(" - Current customer: %s\n",bookGetCustomer(base->elem));
			}
			else
			{
				printf("\n");
			}
			base = base->next;

		}
	}
	else
	{
		printf("There are no books in the library.\n");
	}
}
//Shows a desired book by calling getBookIdentifier method
void specificBook()
{
	printf("Enter the detail of book to be shown \n");
	int convertedID = getBookIdentifier();
	Book* found = controllerGetById(contr,convertedID);
	if (found==NULL)
	{
		printf("Book not found.\n");
	}
	else
	{
		printf("ID: %s - Author: %s - Name: %s - Year: %d - Price: %d - Loaned: %s - LoanCount: %d",getBookIDS(convertedID),bookgetAuthor(found),bookgetName(found),bookgetYear(found),bookgetPrice(found),bookIsLoaned(found)==1?"Yes":"No",bookgetLoanCount(found));
		if (bookIsLoaned(found))
		{
			printf(" - Current customer: %s\n",bookGetCustomer(found));
		}
		else
		{
			printf("\n");
		}
	}
}
//Showing the most rented and less rented book by calling the sort (controllerSort) method
void popular()
{
	printf("Enter 2 for most popular books\n");
	printf("Enter 1 for least popular books\n");
	int sort = readNumber();
	int size = controllerGetSize(contr);
	if (size!=0)
	{
		Book** base = controllerSort(contr,sort,size);
		int i=0;
		for (i=0;i<size;i++)
		{
			printf("Author: %s - Name: %s - Year: %d - Price: %d - Loaned: %s - LoanCount: %d",bookgetAuthor(base[i]),bookgetName(base[i]),bookgetYear(base[i]),bookgetPrice(base[i]),bookIsLoaned(base[i])==1?"Yes":"No",bookgetLoanCount(base[i]));
			if (bookIsLoaned(base[i]))
			{
				printf(" - Current customer: %s\n",bookGetCustomer(base[i]));
			}
			else
			{
				printf("\n");
			}

		}
	}
	else
	{
		printf("There are no books.\n");
	}
}
//Filtering all books by price, calling the bookgetPrice method
void priceSearch()
{
	printf("Please enter a price:");
	int price = readNumber();

	printf("Enter 1 to show all books cheaper than the given price\n");
	printf("Enter 2 to show all books more expensive than the given price\n");
	int sort = readNumber();

	int size = controllerGetSize(contr);
	if (size!=0)
	{
		int tmpSize = 0;
		LinearNode* base = controllerGetAll(contr,&tmpSize);
		printf("The requested books are:\n");
		int i=0;
		int foundBooks=0;
		for (i=0;i<size;i++)
		{
			if ((bookgetPrice(base->elem)<=price && sort==1)||(bookgetPrice(base->elem)>=price && sort==2))
			{
				printf("ID: %s - Author: %s - Name: %s - Year: %d - Price: %d - Loaned: %s - LoanCount: %d",getBookIDS(base->id),bookgetAuthor(base->elem),bookgetName(base->elem),bookgetYear(base->elem),bookgetPrice(base->elem),bookIsLoaned(base->elem)==1?"Yes":"No",bookgetLoanCount(base->elem));
				if (bookIsLoaned(base->elem))
				{
					printf(" - Current customer: %s\n",bookGetCustomer(base->elem));
				}
				else
				{
					printf("\n");
				}
				foundBooks++;
			}
			base = base->next;

		}
		if (foundBooks==0)
		{
			printf("No books were found that match your request.\n");
		}
	}
	else
	{
		printf("There are no books in the library.\n");
	}
}
//Verifyies if the user enters the book identifier accordingly
int getBookIdentifier()
{
	printf("Book identifier (8 digit number in the form xxxx-xxxx): ");

	bool ok=true;

	char id[20];
	do
	{
		ok=true;
		int i = 0;

		for (i=0;i<9;i++)
		{
			id[i]=0;
		}
		scanf("%s", id);

		for (i=0;i<9;i++)
		{
			if (i==4)
			{
				if (id[i]!='-')
				{
					ok = false;
					break;
				}
			}
			else
			{
				if (!((id[i]-'0')<=9 && (id[i]-'0')>=0))
				{
					ok=false;
					break;
				}
			}
		}
		if (!ok)
		{
			printf("Invalid book identifier. Please re-enter.\n");
		}
	}while(!ok);

	int convertedID = getBookID(id);
	return convertedID;
}
