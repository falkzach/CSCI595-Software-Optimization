#include "../Clock.hpp"
#include <omp.h>
#include <iostream>

const bool am_i_alive[2][9] = {
	{false, false, false, true, false, false, false, false, false},
	{false, false, false, true, true, false, false, false, false}
};

const unsigned char padding = 32;

void advance(bool*cur, bool*prev, const unsigned int R, const unsigned int C) {
	unsigned int i, j;
	#pragma omp parallel for private(j) schedule(dynamic, 3)
	for(i=padding; i<R+padding; ++i) {
		for (j=padding; j<C+padding; ++j) {
			unsigned char living_neighbors = 0;
			#pragma omp simd reduction(+:living_neighbors)
			for (char r=-1; r<=1; ++r) {
				for (char c=-1; c<=1; ++c) {
					living_neighbors += (prev[(r+i) * (C+ (padding * 2)) + (c+j)]);
				}
			}

			const bool is_this_cell_living = (prev[i * (C+ (padding * 2)) + j]);
			cur[i * (C+ (padding * 2)) + j] = am_i_alive[is_this_cell_living][living_neighbors];
		}
	}
}

void print_board(bool*board, const unsigned int R, const unsigned int C) {
	for(unsigned int i=padding; i<R+padding; ++i) {
		for (unsigned int j=padding; j<C+padding; ++j) {
			std::cout << int(board[i * (C+ (padding * 2)) + j]);
		}
		std::cout << std::endl;
	}
}

int main(int argc, char**argv) {
	if (argc == 3) {
		srand(0);

		const unsigned int R = 1<<10;
		const unsigned int C = 1<<11;

		unsigned int NUM_REPS = atoi(argv[1]);
		bool print = bool(atoi(argv[2]));

		bool*prev = (bool*)calloc((R+ (padding * 2))*(C+ (padding * 2)),sizeof(bool));
		bool*cur = (bool*)calloc((R+ (padding * 2))*(C+ (padding * 2)),sizeof(bool));

		for(unsigned int i=padding; i<R+padding; ++i) {
			for (unsigned int j=padding; j<C+padding; ++j) {
				cur[i*(C+ (padding * 2))+j] = (rand() % 2 == 0);
			}
		}

		if (print) {
			print_board(cur, R, C);
		}

		Clock c;

		for (unsigned int rep=0; rep<NUM_REPS; ++rep) {
			std::swap(cur, prev);
			advance(cur, prev, R, C);
		}

		c.ptock();

		if (print) {
			print_board(cur, R, C);
		}

	} else {
		std::cerr << "usage game-of-life <generations> <0:don't print, 1:print>"
		<< std::endl;
	}
	return 0;
}
