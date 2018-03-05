#include "./Clock.hpp"
#include <set>
#include <map>

template <typename T>
class Alternative_Set {
private:
	unsigned long _size;
	unsigned long _capacity;
	T*__restrict _data;
public:
	Alternative_Set(T t):
		_data(t)
	{
		//TODO: cache hashes?
	}

	~Alternative_Set() {
		delete[] _data;
	}

	const T & operator [](unsigned long i) const {
		return _data[i];
	}

	T & operator [](unsigned long i) {
		return _data[i];
	}
};

int main() {
	const unsigned long NUMBER_SETS = 1<<18;
	const unsigned long SET_INSERTIONS = 1<<8;
	const unsigned long MAX_ELEMENTS_PLUS_ONE = 1<<8;

	srand(0);

	Clock c;

	std::set<std::set<unsigned int> > collection_of_sets;
	for (unsigned int i=0; i<NUMBER_SETS; ++i) {
		std::set<unsigned int> st;
		for (unsigned int j=0; j<SET_INSERTIONS; ++j) {
			st.insert( rand() % MAX_ELEMENTS_PLUS_ONE);
		}
		collection_of_sets.insert(st);
	}

	//won't compile with templated functor?
	Alternative_Set<std::set<unsigned int>> collection_of_alt_set(collection_of_sets);

	c.ptock();

	return 0;
}
