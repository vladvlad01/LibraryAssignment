/*
 * linearlist.c
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */
#include "LinearListInterface.h"
//This is a Liniar List Data Structure
LinearList* linearlistInit()
{
	//Creating a new linear list with the size 0 and no elements
	LinearList* this = (LinearList*)malloc(sizeof(LinearList));
	this->size = 0;
	this->base = NULL;
	return this;
}
void linearlistDestroy(LinearList* this,void* (*destroyer)(Element))
{
	//Destroying the linear list and each of it's elements with the help of the "destroyer" function which has to be given as a parameter by the caller.
	LinearNode *element = this->base;
	LinearNode *backup = NULL;
	while (element!=NULL)
	{
		backup = element;
		element = element->next;
		destroyer(backup->elem);//TODO fa free la backup->elem
		free(backup);
	}
	free(this);
}
bool linearlistGetSize(LinearList* this)
{
	//Returns the number of elements in the list
	return this->size;
}
bool linearlistAddObject(LinearList* this,int id,Element toAdd,Element (*creator)(Element))
{
	//Adds a new copy of the given element (which can be Book or anything else, because Element is a void*) in the linked list. Returns the success.
	if (!isValidID(this,id))
	{
		if (this->base==NULL)
		{
			this->base = (LinearNode*)malloc(sizeof(LinearNode));
			this->base->elem = creator(toAdd);
			this->base->next=NULL;
			this->base->id=id;
		}
		else
		{
			LinearNode* toAdd2 = (LinearNode*)malloc(sizeof(LinearNode));
			toAdd2->elem=creator(toAdd);
			toAdd2->next=this->base;
			toAdd2->id=id;
			this->base = toAdd2;
		}
		this->size++;
		return true;
	}
	else
	{
		return false;
	}
}
bool isValidID(LinearList* this,int id)
{
	//Returns true if there is an element in the linked list with the given ID
	LinearNode *backup = this->base;
	bool ok = false;
	while (backup!=NULL)
	{
		if (backup->id==id)
		{
			ok=true;
			break;
		}
		backup = backup->next;
	}
	return ok;
}
Element linearlistGetByID(LinearList* this, int id)
{
	//Returns a pointer to the element in the list with the given ID. Returns NULL if there is none.
	if (isValidID(this,id))
	{
		LinearNode *backup = this->base;
		while (backup!=NULL)
		{
			if (backup->id==id)
			{
				return backup->elem;
			}
			backup = backup->next;
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}
LinearNode* getBase(LinearList* this)
{
	//Returns the base(first element) of the lienarlist
	return this->base;
}
bool linearlistDeleteById(LinearList* this, int id,void* (*destroyer)(Element))
{
	//Returns true if an element with the given ID was successfully destroyed by the destroyer function.
	if (isValidID(this,id))
	{
		if (this->base!=NULL)
		{
			if (this->base->id==id)
			{
				LinearNode *backupFirst = this->base;
				this->base = this->base->next;
				destroyer(backupFirst->elem);
				return true;
			}
			else
			{
				if (this->base->next!=NULL)
				{
					LinearNode *backup = this->base;
					while (backup->next!=NULL)
					{
						if (backup->next->id==id)
						{
							LinearNode *toDelete = backup->next;
							backup->next = backup->next->next;

							destroyer(backup->next->elem);
							free(toDelete);
							return true;
						}
						backup = backup->next;
					}
					return false;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
