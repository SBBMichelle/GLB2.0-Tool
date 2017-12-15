/*
 * GLBDisplay.cpp
 *
 *      Author: Michelle
 */

#include "GLB.hpp"
#include "GLBDisplay.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <fstream>



using namespace std;

bool fExists(const char *fileName) {
    std::ifstream ifile(fileName);
    return (bool)ifile;
}

ListEntry curEntry;

void GLBDisplay(const char* inputFilename){

	if(inputFilename == 0x00){
		cout << "Not enough arguments." << endl;
		cout << "Usage: Display <filename>" << endl;
		return;
	}
	else if (fExists(inputFilename)== 0){
		cout << "Specified file doesn't exist." << endl;
		return;
	}


	/////////////////////////
	// Load File

	FILE *f;
	unsigned fileSize;

	f = fopen(inputFilename, "r");

	fseek(f, 0, SEEK_END); // seek to end of file
	fileSize = ftell(f); // get current file pointer
	fseek(f, 0, SEEK_SET); // seek back to beginning of file
	cout << "Filesize is: " << fileSize << " bytes, or:" << "0x" << hex <<uppercase << fileSize << nouppercase << dec << endl;

	void* buffer = malloc(fileSize);
	if (buffer == 0){cout << "Failed to allocate memory to copy the file into." << endl; return;}

	fread(buffer, sizeof(char), fileSize, f);
	if (ferror(f) != 0) {cout << "Error copying file into memory." << endl; return;}

	fclose(f);


	/////////////////////////
	// Check if the loaded file is a GLB2.0 file.

	if (GLBIdentifier == (char*)buffer){
		cout << "Identifier: " << (char*)buffer << endl;}
	else {
		cout << "Input file is not a GLB2.0 file." << endl; return;}


	/////////////////////////
	// Listing Function

	unsigned entriesInGLB = *((unsigned*)buffer + (8/4));
	cout << "File entries in this GLB file: "<< entriesInGLB << endl;

	cout << endl << left << setw(20) << "Name:" << setw(14) << "File Offset:" << setw(14) << "File Size:" << endl << endl;

	unsigned currentEntry = 0;

	while(currentEntry < entriesInGLB){
		unsigned* currentAddress = (unsigned*)buffer + 0xC/4 + (currentEntry*0x1C/4);
		char* nameOfEntry = (char*)currentAddress + 0xC;
		unsigned offsetOfEntry = *(currentAddress + 1);
		unsigned sizeOfEntry = *(currentAddress + 2);

		cout << left << setw(20) << nameOfEntry;
		if ((offsetOfEntry == sizeOfEntry) == 0){
		cout << hex << right << "0x" << uppercase << setfill('0') << setw(8) << offsetOfEntry << "    " << nouppercase << "0x" <<uppercase << setw(8) << sizeOfEntry;
		}
		cout << dec << left << setfill(' ') << endl;
		currentEntry++;
	}
	return;
}

