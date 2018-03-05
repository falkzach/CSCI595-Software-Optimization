#include "./Clock.hpp"
#include <iostream>
#include <assert.h>
#include <math.h>

template <typename T>
class Vector {
private:
	unsigned long _size;
	unsigned long _capacity;
	T*__restrict _data;
	unsigned long _copies;
	unsigned long _memdif;
public:
	Vector():
		_size(0),
		_capacity(4),
		_data( new T[_capacity]),
		_copies(0),
		_memdif(0)
	{	}

	Vector(unsigned long sz):
		_size(sz),
		_capacity(sz),
		_data( new T[_capacity]),
		_copies(0),
		_memdif(0)
	{	}

	~Vector() {
		delete[] _data;
	}

	void push_back(const T & element) {
		// int old_addr, new_addr;
		int diff;
		if(_capacity == _size) {
			_capacity += (unsigned long) (_capacity * 1.61 + 1);
			// _capacity += (unsigned long) (_size / log(_size + 1));
			T*__restrict new_data = new T[_capacity];

			for (unsigned long i=0; i<_size; ++i) {
				new_data[i] = _data[i];
			}
			diff = abs(_data - new_data);
			delete[] _data;
			_data = new_data;
			++_copies;
		}

		_data[_size] = element;
		++_size;

		// diff = abs(old_addr - new_addr);
		if(diff > _memdif) {
			_memdif = diff;
		}
	}

	const T & operator [](unsigned long i) const {
		return _data[i];
	}

	T & operator [](unsigned long i) {
		return _data[i];
	}

	unsigned long get_copies() {
		return _copies;
	}

	unsigned long get_memdiff() {
		return _memdif;
	}
};

int main(int argc, char**argv) {
	if (argc == 2) {
		unsigned int N = atoi(argv[1]);
		// const unsigned long N = 128000;
		const unsigned long REPS = 128;

		Clock c;

		for (unsigned int r=0; r<REPS; ++r) {
			Vector<int> vec;
			for(unsigned int i=0; i<N; ++i) {
				vec.push_back(i);
			}
			std::cout << "copies = " << vec.get_copies() << std::endl;
			std::cout << "max memory addr difference = " << vec.get_memdiff() << std::endl;
		}
		c.ptock();
	} else {
		std::cerr << "usage vector <N>"
		<< std::endl;
	}

	return 0;
}
