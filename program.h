#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include "clause.h"
#include "predicate.h"

class Program {
	public:
		std::vector<Clause> clauses;
		std::vector<Clause> find_rules(Predicate& predicate);
		void show();
	private:
		std::vector<Clause>::iterator iter;
};

#endif
