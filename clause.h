#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>
#include "predicate.h"

class Clause {
	public:
		Clause();
		Predicate head;
		std::vector<Predicate> body;
		bool fact();
		void show();
		float fuzzyness;
		void rename_variables();
		static int rename_counter;
	private:
		std::vector<Predicate>::iterator iter;
};	

#endif
