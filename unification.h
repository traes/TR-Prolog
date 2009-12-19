#ifndef UNIFICATION_H
#define UNIFICATION_H

#include "predicate.h"
#include "varbinding.h"

class Unification{
	public:
		bool unify(Predicate& p,Predicate& q,VarBinding& bindings);
	private:
		bool name_match(Predicate& p, Predicate& q);
		bool arguments_match(Predicate& p, Predicate& q,VarBinding& bindings);
		bool argument_match(Argument& x,Argument& y,VarBinding& bindings);
};

#endif
