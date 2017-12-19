/*
 * GLBDisplay.cpp
 *
 *      Author: Michelle
 */


#include "GLBShared.hpp"


using namespace std;


void CMD_GLBList(const char* inputFilename){

	if(inputFilename == NULL){
		cout << "Not enough arguments." << endl;
		cout << "Usage: list <filename> <optional:name to match>" << endl;
		return;
	}
	else if (doesFileExist(inputFilename) == false){
		cout << "Specified file doesn't exist." << endl;
		return;
	}

	void* buffer = loadFileIntoMemory(inputFilename);
	if (buffer == 0){return;}

	if(verifyGLB(buffer) == false){return;}

	printAllGLBEntries(buffer);

	return;
}

void CMD_GLBListMatches(const char* inputFilename, char* nameToMatch){
	if(inputFilename == NULL){
		cout << "Not enough arguments." << endl;
		cout << "Usage: list <filename> <optional:name to match>" << endl;
		return;
	}
	else if (doesFileExist(inputFilename) == false){
		cout << "Specified file doesn't exist." << endl;
		return;
	}

	void* buffer = loadFileIntoMemory(inputFilename);
	if (buffer == 0){return;}

	if(verifyGLB(buffer) == false){return;}

	printMatchingGLBEntries(buffer, nameToMatch);
}


void CMD_GLBExtractFirstMatch(const char* inputFilename, char* nameToMatch){
	if(inputFilename == NULL){
		cout << "Not enough arguments." << endl;
		cout << "Usage: extract raw <glbfile> <assetname>" << endl;
		return;
	}
	else if (doesFileExist(inputFilename) == false){
		cout << "Specified file doesn't exist." << endl;
		return;
	}

	void* buffer = loadFileIntoMemory(inputFilename);
	if (buffer == 0){return;}

	if(verifyGLB(buffer) == false){return;}

	extractRawGLBEntryToFile(buffer, nameToMatch);
}
