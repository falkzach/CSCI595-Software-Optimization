#include "./Clock.hpp"
#include <functional>
#include <set>
#include <unordered_set>
#include <unordered_map>

class SimpleRandomGenerator {
private:
	unsigned long _random_value;

	static unsigned long ROL(unsigned long v, unsigned char shift) {
		return ((((v) >> ((sizeof(v) * 8) - (shift))) | ((v) << (shift))));
	}
public:
	SimpleRandomGenerator(unsigned long seed):
		_random_value(seed)
	{}

	unsigned long next() {
		_random_value = _random_value * 214013L + 2531011L;
		_random_value = ROL(_random_value, 16);
		return _random_value;
	}
};

template <typename T>
class UniversalSetHash {
public:
	static const unsigned long biggest_64_bit_prime = 18446744073709551557ul;

	std::size_t operator() (const std::set<T> & s) const {
		SimpleRandomGenerator srg(0);

		std::hash<T> single_hash;
		std::size_t combined_hash_value = 0;
		for (const T & obj : s) {
			unsigned long single = ( single_hash(obj) * srg.next() ) % biggest_64_bit_prime;
			combined_hash_value += single;
		}
		combined_hash_value += ( s.size() * srg.next() ) % biggest_64_bit_prime;
		return combined_hash_value;
	}
};

int main() {
	const unsigned long NUMBER_SETS = 1<<18;
	const unsigned long SET_INSERTIONS = 1<<8;
	const unsigned long MAX_ELEMENTS_PLUS_ONE = 1<<8;

	srand(0);

	Clock c;

	// std::unordered_set<std::set<unsigned int>, UniversalSetHash<unsigned int> > collection_of_sets;
	std::unordered_map<std::set<unsigned int>, unsigned int, UniversalSetHash<unsigned int> > map_of_sets;
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
