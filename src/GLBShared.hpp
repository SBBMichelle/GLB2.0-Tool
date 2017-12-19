/*
 * GLBShared.hpp
 *
 *      Author: Michelle
 */

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "GLBCMD.hpp"

#ifndef GLBSHARED_HPP_
#define GLBSHARED_HPP_

using namespace std;


bool doesFileExist(const char *fileName);
void* loadFileIntoMemory(const char* inputFilename);
bool verifyGLB(void* memoryAddress);
void printAllGLBEntries(void* buffer);
unsigned findSingleMatchingGLBEntry(void* buffer, char* nameToFind);
unsigned printMatchingGLBEntries(void* buffer, char* nameToFind);
void printGLBEntry(void* buffer, unsigned entryID);
void extractRawGLBEntryToFile(void* buffer, char* nameToExtract);

#endif /* GLBSHARED_HPP_ */
