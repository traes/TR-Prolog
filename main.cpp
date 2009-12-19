#include <iostream>
#include "program.h"
#include "parser.h"
#include "unification.h"
#include "varbinding.h"
#include "evaluation.h"
#include "interpreter.h"

#define TR_PROLOG_VERSION "v1.4"

using namespace std;

void test_parser(){
	Parser parser;
	Program program = parser.parse("test.bla");
	program.show();
}	

void test_unification(){
	// strings
	string vader = "vader";
	string x = "X";
	string y = "Y";
	string donald = "donald";
	string kwik = "kwik";
	// predicatess
	Predicate p(vader);
	Predicate q(vader);
	// arguments
	Argument arg_x = Argument(x);
	Argument arg_y = Argument(y);
	Argument arg_donald = Argument(donald);
	Argument arg_kwik = Argument(kwik);
	// test
	VarBinding binding;
	Unification unification;
	p.arguments.push_back(Argument(x));
	p.arguments.push_back(Argument(kwik));
	q.arguments.push_back(Argument(donald));
	q.arguments.push_back(Argument(x));
	// show result
	cout << "p:";p.show();cout << endl;
	cout << "q:";q.show();cout << endl;
	cout << "match:" << unification.unify(p,q,binding) << endl;;
	binding.show();
}

void test_evaluation(){
	Parser parser;
	Evaluation evaluation;
	VarBinding bindings;
	evaluation.rules = parser.parse("donald.pl");
	string query_string = "vader(A,B).";
	//string query_string = "vader(donald,X).";
	Clause query = parser.parse_query(query_string);
	cout << " - program - :" << endl;evaluation.rules.show();
	cout << " - query - :" << endl;query.show(); cout << endl;
	bool match = evaluation.eval(query.head,bindings);
	cout << " - match: " << match << "- " << endl;
	cout << " - bindings: " << endl;
	bindings.show();
}

int main(){
	cout << "TR-Prolog " << TR_PROLOG_VERSION << " (c) 2006-2007 Thomas Raes " << endl;
	//test_parser();
	//test_unification();
	//test_evaluation();
	Interpreter interpreter;
	interpreter.read_eval_print();
	return 0;
}	
