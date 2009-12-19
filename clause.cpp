#include <iostream>
#include "argument.h"
#include "clause.h"


Clause::Clause(){
	fuzzyness = 1.0;
}	

int Clause::rename_counter = 0;

void Clause::rename_variables(){
	std::vector<Argument>::iterator arg_iter;
	char rename_counter_string_c[8];
	sprintf(rename_counter_string_c,"_%d",rename_counter);
	// rename variables in head
	for(arg_iter = head.arguments.begin(); arg_iter != head.arguments.end(); arg_iter++){
		if (arg_iter->variable){
			arg_iter->name.append(rename_counter_string_c);
		}
	}
	// rename variables in body
	for(iter = body.begin();iter != body.end(); iter++){
		for(arg_iter = iter->arguments.begin(); arg_iter != iter->arguments.end(); arg_iter++){
			if (arg_iter->variable){
				arg_iter->name.append(rename_counter_string_c);
			}
		}
	}
	rename_counter++;
}

void Clause::show(){
	std::cout << "<";
	printf("%.4f; ",fuzzyness);
	head.show();
	if (body.size()){
		std::cout << " :- ";
		iter = body.begin();
		iter->show();
		iter++;
		for(;iter != body.end(); iter++){
			std::cout << ",";
			iter->show();
		}	
	}
	std::cout << ".>";
}	

bool Clause::fact(){
	return (body.empty());
}	
