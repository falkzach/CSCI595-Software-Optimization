#include "./Clock.hpp"
#include <stdlib.h>
#include <iostream>

__attribute__ ((noinline))
void transpose(double*__restrict dest, double*__restrict source, const unsigned long r, const unsigned long c) {
	for (unsigned long i=0; i<r; ++i) {
		for (unsigned long j=0; j<c; ++j) {
			dest[j*r + i] = source[i*c +j];
		}
	}
}

double* square_mat_mul(double* & A, double* & B, unsigned long & N) {
	double* C = new double[N*N](); //value-initialization
	for (unsigned long i=0; i<N; ++i) {
		for (unsigned long j=0; j<N; ++j) {
			for (unsigned long k=0; k<N; ++k) {
				C[(i*N) + j] += ( A[(i*N)+k] * B[(k*N)+j] );
			}
		}
	}
	return C;
}

double* fast_square_mat_mul(double* & A, double* & B, unsigned long & N) {
	double* C = new double[N*N](); //value-initialization
	double* t_B = new double[N*N];
	transpose(t_B, B, N, N);
	for (unsigned long i=0; i<N; ++i) {
		for (unsigned long j=0; j<N; ++j) {
			for (unsigned long k=0; k<N; ++k) {
				C[(i*N) + j] += ( A[(i*N)+k] * B[(j*N)+k] );
			}
		}
	}
	return C;
}

int main() {
	unsigned long N = 1<<10;

	double* A = new double[N*N];
	double* B = new double[N*N];
	double* C;

	for (unsigned long i=0; i<N; ++i) {
		A[i] = i;
		B[i] = N - i;
	}

	Clock c;

	// C = square_mat_mul(A, B, N);
	C = fast_square_mat_mul(A, B, N);

	c.ptock();

	return 0;
}
