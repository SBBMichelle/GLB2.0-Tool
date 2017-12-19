/*
 * GLBShared.cpp
 *
 *      Author: Michelle
 */

#include "GLBShared.hpp"
#include "GLB.hpp"

using namespace std;

////////////////////////////////////////////////
//// Checks									////
////////////////////////////////////////////////


// Checks if the input file exists.
bool doesFileExist(const char *fileName) {
    ifstream ifile(fileName);
    return (bool)ifile;
}

// Verifies if the pointer contains the appropriate string
// to verify that it contains a GLB2.0 file.
bool verifyGLB(void* memoryAddress){

	if (GLBIdentifier == (char*)memoryAddress){
		cout << "Identifier: " << (char*)memoryAddress << endl; return true;}
	else {
		cout << "Input file is not a GLB2.0 file." << endl; return false;}

}



////////////////////////////////////////////////
//// Memory changing operations				////
////////////////////////////////////////////////


// Allocates a buffer with the appropriate size,
// loads the input file into it and returns the pointer.
void* loadFileIntoMemory(const char* inputFilename){
		FILE *f;
	unsigned fileSize;

	f = fopen(inputFilename, "r");

	fseek(f, 0, SEEK_END);	// seek to end of file
	fileSize = ftell(f);	// get current file pointer
	fseek(f, 0, SEEK_SET);	// seek back to beginning of file
	cout << inputFilename << "'s " << "filesize is: " << fileSize << " bytes, or: " << "0x" << setfill('0') << setw(8) << hex << uppercase << fileSize << nouppercase << dec << setfill(' ') << endl;

	void* buffer = malloc(fileSize);
	if (buffer == 0){cout << "Failed to allocate memory to copy the file into." << endl; return NULL;}

	fread(buffer, sizeof(char), fileSize, f);
	if (ferror(f) != 0) {cout << "Error copying file into memory." << endl; return NULL;}

	fclose(f);

	return buffer;
}



// Iterates through the buffer performing actions based on the input given to the function.
// Prints all entries it iterates trough (If printToConsole == true)
// Stops when it reaches the end of the list or a match and returns it's ID (If findMatch == true)
// Outputs 0xFFFFFFFF if no match is found or when not matching.
// RegEx matching should only be used for user instigated searches.
unsigned iterateGLBEntries(void* buffer, unsigned startingInt, bool printToConsole,
		bool findMatch, bool regEx, char* nameToMatch){

	unsigned entriesInGLB = *((unsigned*)buffer + (8/4));

	unsigned currentEntry = startingInt;

	string nameToMatchString;
	if (nameToMatch != 0x00){
	nameToMatchString = nameToMatch;}

	while(currentEntry < entriesInGLB){

		if (printToConsole){printGLBEntry(buffer, currentEntry);}

		if (findMatch){
			unsigned* entryAddress 	= (unsigned*)buffer + 0xC/4 + (currentEntry*0x1C/4);
				char* nameOfEntry 	= (char*)entryAddress + 0xC;
			if(nameToMatchString == nameOfEntry){
				return currentEntry;
			}

		}

		currentEntry++;
	}

	return 0xFFFFFFFF;
}


////////////////////////////////////////////////
//// Console printing functions				////
////////////////////////////////////////////////

// Prints the name, file offset and datasize of the specified entry.
// (Doesn't print the offset and size when the entry is just an identifier.)
void printGLBEntry(void* buffer, unsigned entryID){
	unsigned* entryAddress 	= (unsigned*)buffer + 0xC/4 + (entryID*0x1C/4);
		char* nameOfEntry 	= (char*)entryAddress + 0xC;
	unsigned offsetOfEntry 	= *(entryAddress + 1);
	unsigned sizeOfEntry	= *(entryAddress + 2);

	cout << right << setw(5) << entryID << ":" << setfill(' ') << left << setw(20) << nameOfEntry;
	if ((offsetOfEntry == sizeOfEntry) == 0){
		cout << hex << right << "0x" << uppercase << setfill('0') << setw(8) << offsetOfEntry << "    " << nouppercase << "0x" <<uppercase << setw(8) << sizeOfEntry;
	}
	cout << dec << left << setfill(' ') << endl;
}


void printAllGLBEntries(void* buffer){
	unsigned entriesInGLB = *((unsigned*)buffer + (8/4));
	cout << "File entries in this GLB file: "<< entriesInGLB << endl;
	cout << endl << "ID:   " << left << setw(20) << "Name:" << setw(14) << "File Offset:" << setw(14) << "File Size:" << endl << endl;

	iterateGLBEntries(buffer, false, true, false, false, 0x00);
}


unsigned printMatchingGLBEntries(void* buffer, char* nameToFind){
	unsigned currentID = 0;
	unsigned matchId;
	unsigned foundMatches = 0;

	cout << "Found matches:" << endl;
	cout << endl << "ID:   " << left << setw(20) << "Name:" << setw(14) << "File Offset:" << setw(14) << "File Size:" << endl << endl;
	while (matchId != 0xFFFFFFFF){
		matchId = iterateGLBEntries(buffer, currentID, false, true, true, nameToFind);
		if (matchId != 0xFFFFFFFF){
			printGLBEntry(buffer, matchId);
			foundMatches++;
		}
		else {cout << foundMatches << " matches" << endl;}
		currentID = matchId;
		currentID++;


	}
	return foundMatches;
}



// Returns ID of first match, 0xFFFFFFFF means no match was found
unsigned findSingleMatchingGLBEntry(void* buffer, char* nameToFind){
	return iterateGLBEntries(buffer, 0, false, true, true, nameToFind);}


void extractRawGLBEntryToFile(void* buffer, char* nameToExtract){

	const char* nameOfFile = nameToExtract;

	unsigned idToExtract;
	unsigned foundMatches = printMatchingGLBEntries(buffer, nameToExtract);
	if (foundMatches < 2){
	idToExtract = findSingleMatchingGLBEntry(buffer, nameToExtract);}
	else {
		cout << "Provide ID>";
		cin >> idToExtract;
		cout << endl;
	}

	if(idToExtract==0xFFFFFFFF){cout << "Couldn't find specified name" << endl; return;}

	unsigned* entryAddress 	= (unsigned*)buffer + 0xC/4 + (idToExtract*0x1C/4);
	unsigned offsetOfEntry 	= *(entryAddress + 1);
	unsigned sizeOfEntry	= *(entryAddress + 2);

	uintptr_t ptr_d = offsetOfEntry + (uintptr_t)buffer;

	FILE *ptr_fp;

	if((ptr_fp = fopen(nameOfFile, "wb")) == NULL)
	{
		printf("Unable to open file!\n");
		exit(1);
	}

	if( fwrite((void*)ptr_d, sizeOfEntry, 1, ptr_fp) != 1)
	{
		printf("Extraction error!\n");
		exit(1);
	}else printf("Extraction was successful.\n");
	fclose(ptr_fp);

}

