/*
 * Book.c
 *
 *  Created on: 10 Apr 2017
 *      Author: cioba
 */

#include "BookInterface.h"

//This data structure simulates an Object

void Book_init(Book* this, char* name,char*author,int year,int price)
{
	//Initializing a new book with it's base components (name, author, year, price)
	this->loanCount=0;
	this->loaned=false;
	this->price=price;
	this->year=year;

	this->author=(char*)malloc(sizeof(char)*strlen(author)+1);
	strcpy(this->author,author);
	this->name=(char*)malloc(sizeof(char)*strlen(name)+1);
	strcpy(this->name,name);
	this->customer=NULL;
}
void Book_destroy(Book* this)
{
	//Destroying a book (thus freeing up memory)
	if (this==NULL)
	{
		printf("ERROR: BOOK NULL AT DESTRUCTION\n");
	}
	else
	{
		free(this->author);
		if (this->customer!=NULL)
		{
			free(this->customer);
		}
		free(this->name);
		free(this);
	}
}

Book* BookCopy(Book* this)
{
	//Creating an independent copy of the given book so it is not corrupted.
	Book *copy = (Book*)malloc(sizeof(Book));;
	copy->loanCount=this->loanCount;
	copy->loaned=this->loaned;
	copy->price=this->price;
	copy->year=this->year;
	copy->author=(char*)malloc(sizeof(char)*strlen(this->author)+1);
	strcpy(copy->author,this->author);
	copy->name=(char*)malloc(sizeof(char)*strlen(this->name)+1);
	strcpy(copy->name,this->name);

	copy->customer=NULL;
	if (this->customer!=NULL)
	{
		copy->customer=(char*)malloc(sizeof(char)*strlen(this->customer)+1);
		strcpy(copy->customer,this->customer);
	}
	return copy;
}
////GETTERS////
char* bookgetName(Book* this)
{
	return this->name;
}
char* bookgetAuthor(Book* this)
{
	return this->author;
}
int bookgetYear(Book* this)
{
	return this->year;
}

bool bookIsLoaned(Book* this)
{
	return this->loaned;
}
char* bookGetCustomer(Book* this)
{
	return this->customer;
}
int bookgetLoanCount(Book* this)
{
	return this->loanCount;
}
int bookgetPrice(Book* this)
{
	return this->price;
}

//SETTERS
void bookSetName(Book* this,char* name)
{
	strcpy(this->name, name);
}
void bookSetAuthor(Book* this,char* author)
{
	strcpy(this->author, author);
}
void bookSetYear(Book* this,int year)
{
	this->year = year;
}
void bookSetLoaned(Book* this,bool loaned)
{
	this->loaned = loaned;
}
void bookSetCustomer(Book* this,char* customer)
{
	if (this->customer!=NULL)
	{
		free(this->customer);
	}
	this->customer = (char*)malloc(sizeof(char)*strlen(customer)+1);
	strcpy(this->customer,customer);
}
void bookSetLoanCount(Book* this,int count)
{
	this->loanCount = count;
}
void bookSetPrice(Book* this,int price)
{
	this->price = price;
}

