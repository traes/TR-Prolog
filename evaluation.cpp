#include <iostream>
#include "evaluation.h"
#include "varbinding.h"

Evaluation::Evaluation(){
	trace = false;
	indentation = 0;
}	

bool Evaluation::eval(Predicate& query){
	VarBinding bindings;
	return eval(query,bindings);
}	

bool Evaluation::eval(Predicate& predicate,VarBinding& bindings){
	float fuzzy_value = 1.0;
	bool result = eval(predicate,bindings,fuzzy_value);
	if (result){
		std::cout << "*** match found ***" << std::endl;
		std::cout << "  fuzzy value: " << fuzzy_value << std::endl;
	} else {
		std::cout << "*** no match found ***" << std::endl;

	}
	return result;
}	

bool Evaluation::eval(Predicate& predicate,VarBinding& bindings,float& fuzzy_value){
	if (trace) {
		indentation++;
		indent();
		std::cout << "evaluating ";
		predicate.show();
		std::cout << std::endl;
	}
	bool result = false;
	VarBinding original_bindings = bindings;
	// check all possible rules from the program
	std::vector<Clause> possible_matches = rules.find_rules(predicate);
	std::vector<Clause>::iterator iter;
	for(iter=possible_matches.begin();iter!=possible_matches.end();iter++){
		if (rule_matches(predicate,*iter,bindings,fuzzy_value)){
			result = true;
			break;
		}
	}
	if (!result) bindings = original_bindings;
	if (trace) indentation--;
	return result;
}

bool Evaluation::rule_matches(Predicate& predicate,Clause& original_rule,VarBinding& bindings,float& fuzzy_value){
	bool result = true;
	if (trace){
		indentation++;
		indent();
		std::cout << "checking match between ";
		predicate.show();
		std::cout << " and ";
		original_rule.show();
		std::cout << std::endl;
	}
	// use a copy of the rule with unique variable names
	Clause rule = original_rule;
	rule.rename_variables();
	// keep a copy of the original bindings and fuzzy value in case the match fails
	VarBinding original_bindings = bindings;
	float original_fuzzy_value = fuzzy_value;
	// check the head of the rule
	if (unification.unify(predicate,rule.head,bindings)){
		// check the body of the rule
		std::vector<Predicate> body_predicates = rule.body;
		std::vector<Predicate>::iterator iter;
		float tmp_fuzzy_value = 1.0;
		for(iter=body_predicates.begin();iter!=body_predicates.end();iter++){
			// check predicate from body
			if (!eval(*iter,bindings,tmp_fuzzy_value)){
				result = false;
				break;
			}
			// update fuzzy value
			if (tmp_fuzzy_value < fuzzy_value) fuzzy_value = tmp_fuzzy_value;
		}
	} else {
		result = false;
	}
	// restore the original bindings and fuzzy value if the match failed
	if (!result) {
		bindings = original_bindings;
		fuzzy_value = original_fuzzy_value;
	} else {
		float fuzzy_value_body = fuzzy_value;
		float not_fuzzy_value_body = 1 - fuzzy_value_body;
		float fuzzy_value_head = rule.fuzzyness;
		if (not_fuzzy_value_body > fuzzy_value_head){
			fuzzy_value = not_fuzzy_value_body;
		} else {
			fuzzy_value = fuzzy_value_head;
		}	
		//fuzzy_value *= rule.fuzzyness;
	}
	if (trace){
		indent();
		if (result){
			std::cout << "==> match OK" << std::endl;
		} else {
			std::cout << "==> no match" << std::endl;
		}	
		indentation--;
	}
	return result;
}	

void Evaluation::indent(){
	for(int i=0;i<indentation;i++){
		std::cout << "   ";
	}
}
