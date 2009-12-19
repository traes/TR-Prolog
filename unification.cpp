#include "unification.h"

bool Unification::unify(Predicate& p,Predicate& q,VarBinding& original_bindings){
	bool match = false;
	VarBinding bindings(original_bindings);
	if (name_match(p,q)){
		match = arguments_match(p,q,bindings);
	}
	if (match) original_bindings = bindings;
	return match;
}	

bool Unification::name_match(Predicate& p,Predicate& q){
	bool result = (p.name.compare(q.name) == 0);
	return result;
}

bool Unification::arguments_match(Predicate& p, Predicate& q,VarBinding& bindings){
	bool result = false;
	std::vector<Argument>* p_args = &p.arguments;
	std::vector<Argument>* q_args = &q.arguments;
	if (p_args->size() == q_args->size()){
		std::vector<Argument>::iterator p_arg_iter = p_args->begin();
		std::vector<Argument>::iterator q_arg_iter = q_args->begin();
		while(p_arg_iter != p_args->end()){
			if (!argument_match(*p_arg_iter,*q_arg_iter,bindings)) goto exit;
			p_arg_iter++;
			q_arg_iter++;
		}
		result = true;
	} 
	exit:
	return result;
}	

bool Unification::argument_match(Argument& x,Argument& y,VarBinding& bindings){
	bool result = false;
	if (!x.variable && !y.variable){
		result = (x.name.compare(y.name) == 0);
	} else if (x.variable){
		if (bindings.already_bound(x)){
			result = (y.name.compare(bindings.val(x).name) == 0);
		} else {
			result = true;
			bindings.add_binding(x,y);
		}
		goto exit;
	} else if (y.variable){
		result = argument_match(y,x,bindings);	
	}
	exit:
	return result;
}
