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

void floyd_warshall(double*result, const double*distance_mat, const unsigned int n) {
	// 1. copy in direct distances:
	for (unsigned int i=0; i<n; ++i) {
		for (unsigned int j=0; j<n; ++j) {
			result[i*n+j] = distance_mat[i*n+j];
		}
	}

	//2. Compute shortest paths with dynamic programming
	// for (unsigned int k=0; k<n; ++k) {
		for (unsigned int i=0; i<n; ++i) {
		for (unsigned int k=0; k<n; ++k) {

			for (unsigned int j=0; j<n; ++j) {
				//allow path to pass through vertex k if it is shortest from i to j
				result[i*n+j] = std::min(
					result[i*n+j],
					result[i*n+k] + result[k*n+j]
				);
			}
		}
	}
}

int main() {
	unsigned long N = 1<<10;
	double* distances = (double*) malloc(N*N*sizeof(double));
	double* result = (double*) malloc(N*N*sizeof(double));

	for (unsigned int i=0; i<N; ++i) {
		for (unsigned int j=0; j<N; ++j) {
			if (i < N/2 && j < N/2) {
				distances[i*N+j] = randInRange(0.0, 1000.0);
			} else {
				distances[i*N+j] = std::numeric_limits<double>::max();
			}

		}
	}

	Clock c;
	floyd_warshall(result, distances, N);
	c.ptock();

	//print
	for (unsigned int i=0; i<15; ++i) {
		for (unsigned int j=0; j<5; ++j) {
			std::cout<<distances[i*N+j] << ", ";
		}
		std::cout << std::endl;
	}

	return 0;
}