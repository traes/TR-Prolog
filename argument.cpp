#include <iostream>
#include <assert.h>
#include "argument.h"

Argument::Argument(std::string& arg_name){
	name = arg_name;
	char* name_c = (char*)malloc(name.length());
	assert(name_c);
	name_c = (char*)name.c_str();
	char* first = &name_c[0];
	variable = (*first > 64 && *first < 91);
}

void Argument::show(){
	std::cout << name;
}	


