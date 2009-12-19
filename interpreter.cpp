
#include <vector>
#include "interpreter.h"
#include "clause.h"

using namespace std;

Interpreter::Interpreter(){
	stop_flag =  false;
	prompt = "*> ";
	stop_command = "stop";
	add_command = "add";
	remove_command = "remove";
	clear_command = "clear";
	help_command = "help";
	show_command = "show";
	query_command = "query";
	load_command = "load";
	trace_command = "trace";
}	

void Interpreter::read_eval_print(){
	cout << prompt;		
	getline(cin,input);
	dispatch(input);
	if (!stop_flag) read_eval_print();
}

void Interpreter::dispatch(string command){
	if (!command.compare(show_command)){
		show();
	} else if (!command.compare(query_command)){
		query();
	} else if (!command.compare(load_command)){
		load();
	} else if (!command.compare(add_command)){
		add();
	} else if (!command.compare(remove_command)){
		remove();
	} else if (!command.compare(clear_command)){
		clear();
	} else if (!command.compare(stop_command)){
		stop();
	} else if (!command.compare(show_command)){
		show();
	} else if (!command.compare(trace_command)){
		trace();
	} else if (!command.compare(help_command)){
		help();
	} else {
		cout << "ERROR: unknown command" << endl;
		help();
	}		
}

void Interpreter::stop(){
	cout << "Bye!" << endl;
	stop_flag = true;
}

void Interpreter::add(){
	string rule;
	cout << "enter rule: ";
	getline(cin,rule);
	evaluator.rules.clauses.push_back(parser.parse_line(rule));
}

void Interpreter::remove(){
	int number = 0;
	vector<Clause>::iterator iter;
	for(iter=evaluator.rules.clauses.begin();iter!=evaluator.rules.clauses.end();iter++){
		cout << number << ": ";
		iter->show();
		cout << endl;
		number++;
	}
	string remove_number;
	cout << "enter rule number:";
	getline(cin,remove_number);
	unsigned int remove = atoi(remove_number.c_str());
	iter = evaluator.rules.clauses.begin();
	if (remove < evaluator.rules.clauses.size()){
		iter += remove;
		evaluator.rules.clauses.erase(iter);
	} else {
		cout << "ERROR: invalid number" << endl;
	}	
}

void Interpreter::clear(){
	evaluator.rules.clauses.clear();
}

void Interpreter::show(){
	evaluator.rules.show();	
}
void Interpreter::help(){
	cout << "show: show all rules" << endl;
	cout << "add: add new rule" << endl;
	cout << "load: load rules from file" << endl;
	cout << "remove: remove rule" << endl;
	cout << "clear: remove all rules" << endl;
	cout << "help: show commands" << endl;
	cout << "stop: stop program" << endl;
	cout << "query: evaluate query" << endl;
	cout << "trace: enable/disable tracing" << endl;
}

void Interpreter::query(){
	cout << "enter query: ";
	std::string query_string;
	getline(cin,query_string);
	Clause query = parser.parse_query(query_string);
	VarBinding bindings;
	bool match = evaluator.eval(query.head,bindings);
	if (match) {
		cout << "  variable bindings:" << endl;
		bindings.show_relevant(query.head);
	}
}	

void Interpreter::load(){
	cout << "enter filename:";
	string filename;
	getline(cin,filename);
	Program program_from_file = parser.parse((char*)filename.c_str());
	vector<Clause>::iterator iter;
	for(iter=program_from_file.clauses.begin();iter!=program_from_file.clauses.end();iter++){
		evaluator.rules.clauses.push_back(*iter);
	}
}

void Interpreter::trace(){
	evaluator.trace = !evaluator.trace;
	if (evaluator.trace){
		std::cout << "tracing enabled" << std::endl;
	} else {
		std::cout << "tracing disabled" << std::endl;
	}	
}
