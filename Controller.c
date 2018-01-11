/*
 * Controller.c
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */


#include "ControllerInterface.h"
#include "LinearListInterface.h"


//These data structure will help to make changes in the Linear List without accessing it from the main file.

Controller* controllerInit(LinearList* list)
{
	//Creating a new controller based on the linearlist given
	Controller* this = (Controller*)malloc(sizeof(Controller));
	this->list = list;
	return this;
}
void controllerDestroy(Controller* this)
{
	//Destroying a controller
	linearlistDestroy(this->list,Book_destroy);
	free(this);
}

bool controllerAdd(Controller* this,int id,Book* theBook)
{
	//Adding a copy of the book in the lienarlist
	return linearlistAddObject(this->list,id,theBook,BookCopy);
}
int controllerGetSize(Controller* this)
{
	//Returns the size of the linearlist
	return linearlistGetSize(this->list);
}
bool controllerRemove(Controller* this, int ID)
{
	//Removes (and destroys) a book by the given ID
	return linearlistDeleteById(this->list,ID,Book_destroy);
}
Book* controllerGetById(Controller* this,int id)
{
	//Returns a pointer to the book in the linearlist with the given ID
	return linearlistGetByID(this->list,id);
}
bool controllerLoanBook(Controller* this,int id,char* customerName)
{
	//Returns true if a book with the given ID and customerName has been successfully loaned, false otherwise
	if (!isValidID(this->list,id))
	{
		return false;
	}
	else
	{
		Book *buc = linearlistGetByID(this->list,id);
		if (!bookIsLoaned(buc))
		{
			buc ->loaned=true;
			buc->loanCount++;
			if (buc->customer!=NULL)
			{
				free(buc->customer);
				buc->customer=NULL;
			}

			buc->customer = (char*)malloc(sizeof(char)*strlen(customerName)+1);
			strcpy(buc->customer,customerName);
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool controllerReturnBook(Controller* this,int id)
{
	//Returns true if a book with the given ID has been successfully returned, false otherwise
	if (!isValidID(this->list,id))
	{
		return false;
	}
	else
	{
		Book *buc = linearlistGetByID(this->list,id);
		if (bookIsLoaned(buc))
		{
			buc ->loaned=false;
			if (buc->customer!=NULL)
			{
				free(buc->customer);
				buc->customer=NULL;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}

LinearNode* controllerGetAll(Controller* this,int *size)
{
	//Returns the first element of the linearlist and it's size with the help of the size parameter
	int tmpSize = linearlistGetSize(this->list);
	size = &tmpSize;
	return getBase(this->list);
}

//////SORTING FUNCTIONS////////
int _controllerLoanASC(const void* a, const void* b)
{
	Book* cha = *(Book**)a;
	Book* chb = *(Book**)b;

	return bookgetLoanCount(cha) -  bookgetLoanCount(chb);
}
int _controllerLoanDSC(const void* a, const void* b)
{
	Book* cha = *(Book**)a;
	Book* chb = *(Book**)b;

	return bookgetLoanCount(chb) -  bookgetLoanCount(cha);
}
//////////////////

Book** controllerSort(Controller* this,int asc,int size)
{
	//Returns a pointer to a pointer of a book list of the given size that is stored accordingly (ascending/descending).
	int (*cmp)(const void* a, const void* b) = NULL;

	if (asc==1)
		cmp = &_controllerLoanASC;
	else
		cmp = &_controllerLoanDSC;

	Book** toSort = (Book**)malloc(sizeof(Book*)*size);
	LinearNode* base = getBase(this->list);
	int i=0;
	for (i=0;i<size;i++)
	{
		toSort[i]=BookCopy(base->elem);
		//
		base = base->next;
	}

	qsort(toSort,size, sizeof(Book*), cmp);
	return toSort;
}
