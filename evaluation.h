#ifndef EVALUATION_H
#define EVALUATION_H

#include <vector>
#include "unification.h"
#include "clause.h"
#include "program.h"
#include "predicate.h"

class Evaluation {
	public:
		Evaluation();
		bool eval(Predicate& predicate);
		bool eval(Predicate& predicate,VarBinding& bindings);
		bool eval(Predicate& predicate,VarBinding& bindings,float& fuzzy_value);
		bool rule_matches(Predicate& predicate,Clause& rule,VarBinding& bindings,float& fuzzy_value);
		bool trace;
		Program rules;
	private:
		Unification unification;
		int indentation;
		void indent();
};

#endif
