/*
 * FileManager.h
 *
 *  Author: Vlad Ciobanu
 *  Student ID: C15716369
 */
//Abstract Data Type definition for the FileManager
#ifndef FILEMANAGERINTERFACE_H_
#define FILEMANAGERINTERFACE_H_
#include "ControllerInterface.h"
#include "UtilsInterface.h"
void writeData(Controller* contr);
void readData(Controller* contr);
#endif /* FILEMANAGERINTERFACE_H_ */
