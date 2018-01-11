/*
 * Controller.h
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */

#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_

#include "BookInterface.h"
#include "LinearListInterface.h"
//Abstract Data Type definition for a Controller
typedef struct struct_Controller
{
	LinearList* list;
}Controller;

Controller* controllerInit(LinearList* list);
void controllerDestroy(Controller* this);

bool controllerAdd(Controller* this,int id,Book* theBook);
bool controllerRemove(Controller* this, int ID);
Book* controllerGetById(Controller* this,int id);
bool controllerLoanBook(Controller* this,int id,char* customerName);
bool controllerReturnBook(Controller* this,int id);
int controllerGetSize(Controller* this);

LinearNode* controllerGetAll(Controller* this,int *size);
Book** controllerSort(Controller* this,int asc,int size);

#endif /* CONTROLLERINTERFACE_H_ */
