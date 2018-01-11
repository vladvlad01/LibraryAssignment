/*
 * Book.h
 *
 *  Created on: 10 Apr 2017
 *      Author: cioba
 */

#ifndef BOOKINTERFACE_H_
#define BOOKINTERFACE_H_
#include "UtilsInterface.h"

//Abstract Data Type definition for a Book
typedef struct struct_book
{
	char *name;
	char *author;
	int year;
	bool loaned;
	char *customer;
	int loanCount;
	int price;
}Book;

void Book_init(Book* this, char* name,char*author,int year,int price);
void Book_destroy(Book* this);

Book* BookCopy(Book* this);
char* bookgetName(Book* this);
char* bookgetAuthor(Book* this);
int bookgetYear(Book* this);
bool bookIsLoaned(Book* this);
char* bookGetCustomer(Book* this);
int bookgetLoanCount(Book* this);
int bookgetPrice(Book* this);

void bookSetName(Book* this,char* name);
void bookSetAuthor(Book* this,char* author);
void bookSetYear(Book* this,int year);
void bookSetLoaned(Book* this,bool loaned);
void bookSetCustomer(Book* this,char* customer);
void bookSetLoanCount(Book* this,int count);
void bookSetPrice(Book* this,int price);

#endif /* BOOKINTERFACE_H_ */
