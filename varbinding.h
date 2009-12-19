#ifndef VAR_BINDING_H
#define VAR_BINDING_H

#include <map>
#include <string>
#include "argument.h"
#include "predicate.h"

class VarBinding{
	public:
		VarBinding(){};
		std::map<std::string,Argument> map;
		bool already_bound(Argument& var);
		Argument val(Argument& val);
		Argument val(std::string& val);
		void add_binding(Argument& var,Argument& val);
		void show();
		void show_relevant(Predicate& predicate);
};		

#endif
