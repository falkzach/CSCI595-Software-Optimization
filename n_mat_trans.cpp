#include "./Clock.hpp"
#include <iostream>

__attribute__ ((noinline))
void transpose(double*__restrict dest, double*__restrict source, const unsigned long r, const unsigned long c) {

	int count = 0;
	for (unsigned long i=0; i<r; ++i) {
		for (unsigned long j=0; j<c; ++j) {
			dest[j*r + i] = source[i*c +j];
			++count;
		}
	}
	std::cout<<"count: "<< count<<std::endl;
}

int main() {
	unsigned long N = 1<<10;
	unsigned long R = N;
	unsigned long C = N;
	double * matrix = new double[R*C];
	for (unsigned long i=0; i<R*C; ++i) {
		matrix[i] = i;
	}

	Clock c;
	double * result = new double[R*C];
	transpose(result, matrix, R, C);
	std::cout<<"nxn: "<< N*N <<std::endl;
	c.ptock();

	return 0;
}
