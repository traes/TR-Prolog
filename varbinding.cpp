#include <assert.h>
#include <iostream>
#include "varbinding.h"

bool VarBinding::already_bound(Argument& var){
	return (map.count(var.name) > 0);
}	

Argument VarBinding::val(Argument& var){
	return val(var.name);
}	

Argument VarBinding::val(std::string& var_name){
	std::map<std::string,Argument>::iterator iter;
	Argument result;
	iter = map.find(var_name);
	assert(iter != map.end());
	if (iter->second.variable && already_bound(iter->second)){
		result = val(iter->second);
	} else {	
		result = iter->second;
	}	
	return result;
}

void VarBinding::add_binding(Argument& var,Argument& val){
	map[var.name]=val;
}	

void VarBinding::show(){
	std::map<std::string,Argument>::iterator iter;
	std::string var_name;
	std::cout << "	{" << std::endl;
	iter = map.begin();
	if (iter != map.end()) {
		var_name = iter->first;
		std::cout << "		" << iter->first << " => " << val(var_name).name;
		iter++;
	}
	for(;iter != map.end(); iter++){
		std::cout << "," << std::endl;
		var_name = iter->first;
		std::cout << "		" <<  iter->first << " => " << val(var_name).name;
	}
	std::cout << std::endl << "	}" << std::endl;
}

void VarBinding::show_relevant(Predicate& predicate){
	std::vector<Argument>::iterator iter;
	std::string var_name;
	std::cout << "	{" << std::endl;
	iter = predicate.arguments.begin();
	if (iter != predicate.arguments.end()) {
		if (iter->variable){
			var_name = iter->name;
			std::cout << "		" << var_name << " => " << val(var_name).name;
		}
		iter++;
	}
	for(;iter != predicate.arguments.end(); iter++){
		if (iter->variable){
			std::cout << "," << std::endl;
			var_name = iter->name;
			std::cout << "		" <<  var_name << " => " << val(var_name).name;
		}
	}
	std::cout << std::endl << "	}" << std::endl;
}
