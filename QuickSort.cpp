#include "Clock.hpp"
#include <cassert>
#include <iostream>

int randomIntInRange(int min, int max) {
	assert(max >= min);
	return rand() % (max + 1 - min) + min;
}

void selection_sort(unsigned long*source, const unsigned long n) {
	for (unsigned long i=0; i<n; ++i) {
		for (unsigned long j=i+1; j<n; ++j) {
			if(source[j] < source[i]) {
				std::swap(source[i], source[j]);
			}
		}
	}
}

// an in place recursive quick sort implementation
//random pivot
//no memory allocations
//no buffer

void quick_sort(
	unsigned long *source,
	const unsigned long n,
	const unsigned long k,
	unsigned long start = 0,
	unsigned long stop = 0
) {

	if (n <= k) {
		selection_sort(source, n);
		return;
	}

	if (stop == 0) {
		stop = n;
	}

	unsigned long length = stop - start;
	unsigned long pivot = randomIntInRange(start, stop - 1);
	unsigned long left = start + 1;
	unsigned long right = stop;

	std::swap(source[start], source[pivot]);
	while (left < right) {
		//TODO: make consts for values that get prepared (inlining), i.e.:
		const unsigned long start_val = source[start];
		if (source[left] <= start_val) {
			left += 1;
		} else {
			std::swap(source[left], source[right - 1]);
			right -= 1;
		}
	}
	std::swap(source[start], source[left - 1]);
	if (left - 1 - start > 1) {
		quick_sort(source, n, k, start, left - 1);
	}
	if (stop - right > 1) {
		quick_sort(source, n, k, right, stop);
	}
}

int main(int argc, char**argv) {
	if(argc == 3) {
		const unsigned long N = atoi(argv[1]);
		const unsigned long K = atoi(argv[2]);

		unsigned long*x = new unsigned long[N];

		for (unsigned long i=0; i<N; ++i) {
			x[i] = N-i;
		}

		Clock c;
		quick_sort(x, N, K);
		c.ptock();

	} else {
		std::cerr << "Usage: sort <n> <k>" <<std::endl;
	}
	return 0;
}
