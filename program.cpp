#include "program.h"
#include <iostream>

void Program::show(){
	for(iter=clauses.begin();iter!=clauses.end();iter++){
		iter->show();
		std::cout << std::endl;
	}
}	

std::vector<Clause> Program::find_rules(Predicate& predicate){
	std::vector<Clause> result;
	for(iter=clauses.begin();iter!=clauses.end();iter++){
		if (iter->head.compatible(predicate)) result.push_back(*iter);	
	}
	return result;
}
