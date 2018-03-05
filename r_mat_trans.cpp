#include "./Clock.hpp"
#include <iostream>

constexpr unsigned int BLOCK_SIZE = 4;

static int buffered_helper(
	double*__restrict dest, double*__restrict source, const unsigned long R, const unsigned long C,
	const unsigned long r_start, const unsigned long r_end, const unsigned long c_start, const unsigned long c_end) {

	unsigned long r_span = r_end - r_start;
	unsigned long c_span = c_end - c_start;

	int count = 0;

	//todo: finish
	if ( r_span <= BLOCK_SIZE && c_span <= BLOCK_SIZE ) {
		for (unsigned long r=r_start; r<r_end; ++r)
			for (unsigned long c=c_start; c<c_end; ++c)
				dest[c*R +r] = source[r*C + c];
				++count;
	} else {
		if (r_span > c_span) {
			count += buffered_helper(dest, source, R, C, r_start, r_start+r_span/2, c_start, c_end);
			count += buffered_helper(dest, source, R, C, r_start+r_span/2, r_end, c_start, c_end);
		} else {
			count += buffered_helper(dest, source, R, C, r_start, r_end, c_start, c_start+c_span/2);
			count += buffered_helper(dest, source, R, C, r_start, r_end, c_start+c_span/2, c_end);
		}
	}
	return count;
}

__attribute__ ((noinline))
int recursive_transpose(double*__restrict dest, double*__restrict source, const unsigned long r, const unsigned long c) {
	return buffered_helper(dest, source, r, c, 0, r, 0, c);
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
	int total = recursive_transpose(result, matrix, R, C);
	c.ptock();
	std::cout<<"count: "<< total<<std::endl;
	std::cout<<"nxn: "<< N*N <<std::endl;

	return 0;
}
