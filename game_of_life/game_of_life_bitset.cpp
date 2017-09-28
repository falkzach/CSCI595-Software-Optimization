#include "../Clock.hpp"
#include <iostream>
#include <bitset>

const bool am_i_alive[2][9] = {
	{false, false, false, true, false, false, false, false, false},
	{false, false, false, true, true, false, false, false, false}
};

template <size_t bitsetsize>
bool advance_single(std::bitset<bitsetsize> &board, const unsigned int R, const unsigned int C, int r, int c) {
	unsigned char living_neighbors = 0;
	for (int i=-1; i<=1; ++i) {
		for (int j=-1; j<=1; ++j) {
			living_neighbors += (board[(r+i) * (C+2) + (c+j)]);
		}
	}

	const bool is_this_cell_living = (board[r * (C+2) + c]);
	return am_i_alive[is_this_cell_living][living_neighbors];
}

template <size_t bitsetsize>
void advance(std::bitset<bitsetsize> &cur, std::bitset<bitsetsize> &prev, const unsigned int R, const unsigned int C) {
	for(unsigned int i=1; i<R+1; ++i) {
		for (unsigned int j=1; j<C+1; ++j) {
			cur[i * (C+2) + j] = advance_single(prev, R, C, i, j);
		}
	}
}

template <size_t bitsetsize>
void print_board(std::bitset<bitsetsize> &board, const unsigned int R, const unsigned int C) {
	for(unsigned int i=1; i<R+1; ++i) {
		for (unsigned int j=1; j<C+1; ++j) {
			std::cout << int(board[i * (C+2) + j]);
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

		std::bitset<(R+2)*(C+2)> prev;
		std::bitset<(R+2)*(C+2)> cur;

		for(unsigned int i=1; i<R+1; ++i) {
			for (unsigned int j=1; j<C+1; ++j) {
				cur[i*(C+2)+j] = (rand() % 2 == 0);
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
