/*
 * Main.cpp
 *
 *      Author: Michelle
 */

#include <iostream>
#include "GLBDisplay.hpp"
using namespace std;

void printHelp() {

	cout << "commands and arguments:" << endl;
	cout << "display <filename>" << endl;

}

int main(int argc, char* argv[]) {

	string test = "test";
	string display = "display";


	if (argc < 2){printHelp();}
	else if (argv[1] == display) {GLBDisplay(argv[2]);}
	else {printHelp();}

	return 0;

}
