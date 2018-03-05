#include <iostream>
#include <cassert>

#include "./Clock.hpp"

double randInRange(double min, double max) {
	assert(max > min);
	return min + (
		((double) rand()) / ((double) RAND_MAX)
		* (max - min)
	);
}

struct complex_number {
	double real;
	double imaginary;
} ;

void populate(complex_number* x, unsigned long N) {
	complex_number cn;
	for (unsigned long i=0; i<N; ++i) {
		cn.real = randInRange(0.0, 1000.0);
		cn.imaginary = randInRange(0.0, 1000.0);
		x[i] = cn;
	}
}

void gauss_multiplication(complex_number* x, complex_number* y, complex_number* z, unsigned long N) {
	double m1, m2;
	complex_number cn;
	for (unsigned long i=0; i<N; ++i) {
		m1 = x[i].real * y[i].real;
		m2 = x[i].imaginary * y[i].imaginary;
		cn.real = m1 - m2;
		cn.imaginary = (
			(x[i].real+x[i].imaginary)*(y[i].real+y[i].imaginary)
			)- m1 - m2;
		z[i] = cn;
	}
}

void naieve(complex_number* x, complex_number* y, complex_number* z, unsigned long N) {
	complex_number cn;
	for (unsigned long i=0; i<N; ++i) {
		cn.real = (x[i].real * y[i].real) - (x[i].imaginary * y[i].imaginary);
		cn.imaginary = (x[i].real * y[i].imaginary) + (x[i].imaginary *y[i].real);
		z[i] = cn;
	}
}

int main() {
	srand(0);

	unsigned long N = 1<<20;

	complex_number* X = (complex_number*) malloc(N * sizeof(complex_number));
	complex_number* Y = (complex_number*) malloc(N * sizeof(complex_number));
	complex_number* ZN = (complex_number*) malloc(N * sizeof(complex_number));
	complex_number* ZG = (complex_number*) malloc(N * sizeof(complex_number));

	populate(X, N);
	populate(Y, N);

	std::cout << "Naieve" << std::endl;
	Clock c;
	naieve(X, Y, ZN, N);
	c.ptock();

	std::cout << "Gauss" << std::endl;
	c.tick();
	gauss_multiplication(X, Y, ZG, N);
	c.ptock();

	for (unsigned long i=0; i<10; ++i) {
		std::cout << "N: " << ZN[i].real << " i" << ZN[i].imaginary << std::endl;
		std::cout << "G: " << ZG[i].real << " i" << ZG[i].imaginary << std::endl;
	}

	return 0;
}