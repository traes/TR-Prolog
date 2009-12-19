#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "program.h"
#include "clause.h"

class Parser {
	public:
		Program parse(char* filename);
		Clause parse_query(std::string& query);
		Clause parse_line(std::string line);
	private:
		Predicate parse_predicate(char* line_c,char*& r);
};		

#endif
