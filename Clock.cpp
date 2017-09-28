#include "Clock.hpp"

const unsigned int N=1<<24;

int main() {
	Clock c;
	unsigned long tot = 0.0;
	for (unsigned int i=0; i<N; ++i) {
		tot += i;
	}
	c.ptock();

	std::cout << tot << std::endl;

	return 0;
}
