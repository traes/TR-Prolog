#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include <string>
#include "argument.h"

class Predicate {
	public:
		Predicate(){};
		Predicate(std::string& name){this->name = name;};
		std::string name;
		std::vector<Argument> arguments;
		bool compatible(Predicate& predicate);
		void show();
	private:
		std::vector<Argument>::iterator iter;
};		

#endif
