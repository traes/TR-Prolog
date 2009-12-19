#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include "parser.h"
#include "program.h"
#include "evaluation.h"

class Interpreter {
	public:
		Interpreter();
		void read_eval_print();
	private:
		// intepreter components
		Parser parser;
		Program program;
		Evaluation evaluator;
		// read_eval_print control
		bool stop_flag;
		std::string prompt;
		std::string input;
		void dispatch(std::string command);
		// command names
		std::string show_command;
		std::string stop_command;
		std::string add_command;
		std::string remove_command;
		std::string clear_command;
		std::string help_command;
		std::string query_command;
		std::string load_command;
		std::string trace_command;
		// command functions
		void stop();
		void show();
		void add();
		void remove();
		void clear();
		void help();
		void query();
		void load();
		void trace();
};		

#endif
