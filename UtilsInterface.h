/*
 * Utils.h
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */

#ifndef UTILSINTERFACE_H_
#define UTILSINTERFACE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Abstract Data Type definition for a boolean and the Utility file.
#define bool int
#define false 0
#define true (!false)

int getBookID(char* id);
char* getBookIDS(int s);
#endif /* UTILSINTERFACE_H_ */
