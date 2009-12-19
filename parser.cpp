#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#include "parser.h"

#define DEBUG false

//form: foo(Bar,bla,42)
Predicate Parser::parse_predicate(char* line_c,char*& r){
	Predicate result;
	// predicate name
	char* predicate_name_c = (char*) malloc(strlen(line_c)); // temp storage for pred. name
	assert(predicate_name_c);
	char *w; // write pointer
	w = &predicate_name_c[0];
	while (*r && *r != '(') *(w++) = *(r++); // copy predicate name to predicate_name_c
	*w = 0; // terminate predicate_name_c 
	result.name = predicate_name_c;
	if(DEBUG) std::cout << "name: " <<  result.name << std::endl;
	// arguments
	char* argument_name_c = (char*) malloc(strlen(line_c)); // temp storage for arg. name
	assert(argument_name_c);
	while(*r && *r != ')'){
		r++;
		w = &argument_name_c[0];
		while (*r && *r != ',' && *r != ')') *(w++) = *(r++); // copy arg. name
		*w = 0;
		std::string argument_name = argument_name_c;
		result.arguments.push_back(Argument(argument_name));
		if(DEBUG) {std::cout << "arg:"; result.arguments.back().show(); std::cout << std::endl;}
	}
	if(*r && (*r == ')')) r++;
	free(predicate_name_c);
	free(argument_name_c);
	return result;
}

//form: <0.1234; foo(Bar,42) :- bla(Bar),test(Bar,42).> 
Clause Parser::parse_line(std::string line){
	Clause clause;
	if(DEBUG) std::cout << std::endl << "line: " << line << std::endl;
	char* line_c = (char*) line.c_str(); // line as C string
	char* r = &line_c[0]; // read pointer
	// read first '<'
	if (*r && *r == '<') r++;
	// read fuzzyness
	char* fuzzyness_c = (char*) malloc(strlen(line_c)); // temp storage for number copy
	assert(fuzzyness_c);
	char* fuzzyness_w = &fuzzyness_c[0]; // write pointer
	while(*r && *r != ';') *(fuzzyness_w++) = *(r++); // copy number 
	*fuzzyness_w = 0; // terminate string with 0
	clause.fuzzyness = atof(fuzzyness_c);
	if(*r && *r == ';') r++;
	// read head
	clause.head = parse_predicate(line_c,r);
	// skip " :- "
	while(*r && (*r == ' ' || *r == ':' || *r == '-')) r++;
	// read body
	while(*r && *r != '.' && *r != '>'){
			clause.body.push_back(parse_predicate(line_c,r));
			r++;
	}
	free(fuzzyness_c);
	return clause;
}	

//form: foo(Bar).
Clause Parser::parse_query(std::string& line){
	Clause clause;
	if(DEBUG) std::cout << std::endl << "line: " << line << std::endl;
	char* line_c = (char*) line.c_str();
	char* r = &line_c[0];
	clause.head = parse_predicate(line_c,r);
	return clause;
}

Program Parser::parse(char* filename){
	Program program;
	std::ifstream input(filename);
	std::string line;
	while(getline(input,line)){
		program.clauses.push_back(parse_line(line));
	}
	input.close();
	return program;
}


