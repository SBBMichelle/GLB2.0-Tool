/*
 * GLBDisplay.hpp
 *
 *      Author: Michelle
 */

#ifndef GLBCMD_HPP_
#define GLBCMD_HPP_

#include <iostream>
using namespace std;

void CMD_GLBList(const char* inputFilename);
void CMD_GLBListMatches(const char* inputFilename, char* nameToMatch);
void CMD_GLBExtractMatch(const char* inputFilename, char* nameToMatch);


#endif /* GLBCMD_HPP_ */
