/*
 * GLB.hpp
 *
 *      Author: Michelle
 */

#ifndef GLB_HPP_
#define GLB_HPP_

#include <iostream>
using namespace std;

string GLBIdentifier = "GLB2.0";


typedef struct {
	unsigned bool_encrypted;
	unsigned data_pointer;
	unsigned data_size;
	char file_name[16];
} ListEntry;



#endif /* GLB_HPP_ */
