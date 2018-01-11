/*
 * linearlist.h
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */

#ifndef LINEARLISTINTERFACE_H_
#define LINEARLISTINTERFACE_H_
#include <stdlib.h>
#include "UtilsInterface.h"

typedef void* Element;

//This structure helps to create nodes for the Linked List; each node has its own ID and creates the actual list
typedef struct repo_element
{
	Element elem;
	struct repo_element *next;
	int id;
}LinearNode;

typedef struct repo
{
	LinearNode *base;
	int size;
}LinearList;

LinearList* linearlistInit();
void linearlistDestroy(LinearList* this,void* (*destroyer)(Element));
bool linearlistGetSize(LinearList* this);
bool linearlistAddObject(LinearList* this,int id,Element toAdd,Element (*creator)(Element));
Element linearlistGetByID(LinearList*, int id);
bool linearlistDeleteById(LinearList*, int id,void* (*destroyer)(Element));
bool isValidID(LinearList*,int id);
LinearNode* getBase(LinearList*);
#endif /* LINEARLISTINTERFACE_H_ */
