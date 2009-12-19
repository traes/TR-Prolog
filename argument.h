#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <string>

class Argument {
	public:
		Argument(){variable = false;};
		Argument(std::string& arg_name);
		std::string name;
		bool variable;
		void show();
};		

#endif
