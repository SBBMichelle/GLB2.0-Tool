/*
 * Main.cpp
 *
 *      Author: Michelle
 */

#include <iostream>

#include "GLBCMD.hpp"
using namespace std;

void printHelp() {

	cout << "commands and arguments:" << endl;
	cout << "   list <filename> <optional:name to find>" << endl;
	cout << "   extract <filename> <asset_name>" << endl;

}

int main(int argc, char* argv[]) {

	string test = "test";
	string list = "list";
	string extract = "extract";
	string raw = "raw";


	if (argc < 2){printHelp();}

	else if (argv[1] == list){
		if(argv[3] == 0x00){
			CMD_GLBList(argv[2]);
		}
		else{
			CMD_GLBListMatches(argv[2], argv[3]);
			}
		}

	else if (argv[1] == extract){
		if(argv[2] == raw){
		CMD_GLBExtractMatch(argv[3], argv[4]);
		}
	}

	else {printHelp();}

	return 0;

}
