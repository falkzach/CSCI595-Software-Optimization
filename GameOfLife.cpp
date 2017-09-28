#include "./Clock.hpp"
#include <iostream>

//Code:
// 00 -> dead now, dead prev
// 01 -> dead now, alive prev
// 10 -> alive now, dead prev
// 11 -> alive now, alive prev
const bool prev_and_alive_neighbors[2][9] = {
	{false, false, false, true, false, false, false, false, false},
	{false, false, true, true, false, false, false, false, false}
};

void advance_single(char*board, const unsigned int R, const unsigned int C, int r, int c) {
	unsigned char living_neighbors = 0;
	for (int i=-1; i<=1; ++i) {
		for (int j=-1; j<=1; ++j) {
			living_neighbors += (board[(r+i) * (C+2) + (c+j)] & 1);
		}
	}
	living_neighbors -= (board[r * (C+2) + c] & 1);

	// bool is_this_cell_living = (board[r * (C+2) + c] & 1);
	// board[r * (C+2) + c] = board[r * (C+2) + c] | prev_and_alive_neighbors[is_this_cell_living][living_neighbors] << 1;
	// return;

	board[r * (C+2) + c] = board[r * (C+2) + c] | ((living_neighbors == 3 || (
		(board[r * (C+2) + c] & 1) && living_neighbors >=2 && living_neighbors
	<= 3)) << 1);
}

void shift_current_to_prev(char*board, const unsigned int R, const unsigned int C) {
	for(unsigned int i=1; i<R+1; ++i) {
		for (unsigned int j=1; j<C+1; ++j) {
			board[i * (C+2) + j] >>= 1;
		}
	}
}

void advance(char*board, const unsigned int R, const unsigned int C) {
	for(unsigned int i=1; i<R+1; ++i) {
		for (unsigned int j=1; j<C+1; ++j) {
			advance_single(board, R, C, i, j);
		}
	}
	shift_current_to_prev(board, R, C);
}

void print_board(char*board, const unsigned int R, const unsigned int C) {
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

		bool*prev = (bool*)calloc((R+2)*(C+2),sizeof(bool));
		char*board = (char*)calloc((R+2)*(C+2),sizeof(char));

		for(unsigned int i=1; i<R+1; ++i) {
			for (unsigned int j=1; j<C+1; ++j) {
				board[i*(C+2)+j] = (rand() % 2 == 0);
			}
		}

		if (print) {
			print_board(board, R, C);
		}

		Clock c;

		for (unsigned int rep=0; rep<NUM_REPS; ++rep) {
			advance(board, R, C);
		}

		c.ptock();

		if (print) {
			print_board(board, R, C);
		}

	} else {
		std::cerr << "usage game-of-life <generations> <0:don't print, 1:print>"
		<< std::endl;
	}
	return 0;
}
