#include "./Clock.hpp"
#include <set>
#include <map>

int main() {
	const unsigned long NUMBER_SETS = 1<<18;
	const unsigned long SET_INSERTIONS = 1<<8;
	const unsigned long MAX_ELEMENTS_PLUS_ONE = 1<<8;

	srand(0);

	Clock c;

	// std::set<std::set<unsigned int> > collection_of_sets;
	std::map<std::set<unsigned int>, int > map_of_sets;
	for (unsigned int i=0; i<NUMBER_SETS; ++i) {
		std::set<unsigned int> st;
		for (unsigned int j=0; j<SET_INSERTIONS; ++j) {
			st.insert( rand() % MAX_ELEMENTS_PLUS_ONE);
		}
		// collection_of_sets.insert(st);
		map_of_sets[st] = st.size();
	}

	for (auto m: map_of_sets) {
		if(m.second % 2 == 1) {
			m.second = 0;
		}
	}

	c.ptock();

	return 0;
}
