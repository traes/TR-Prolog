#include <iostream>
#include "predicate.h"

void Predicate::show(){
	std::cout << name << "(";
	iter = arguments.begin();
	if (iter != arguments.end()) (iter++)->show();
	for(;iter != arguments.end(); iter++){
		std::cout << ",";
		iter->show();
	}	
	std::cout << ")";
}

bool Predicate::compatible(Predicate& predicate){
	bool same_name = (name.compare(predicate.name) == 0);
	bool same_arity = (arguments.size() == predicate.arguments.size());
	return (same_name && same_arity);
}	
