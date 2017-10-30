#include "../Clock.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

// I consent to my name and runtime being posted etc -ZF

const unsigned char nuc_to_code[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 1, 255, 3, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 2, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, };

/*

//This code generates the mask table bellow
#include <iostream>

constexpr long BITS_IN_LONG = (sizeof(long) * 8);



unsigned long bits_to_mask(long bits) {
	unsigned long mask = 0;
	unsigned long gap = BITS_IN_LONG - bits;
	if (bits == 0) {
		return mask;
	}
	for(int i=bits; i >= 0; --i) {
		mask <<= 1;
		mask |= 1;
	}
	mask <<= gap;
	return mask;
}

int main() {
	std::cout << "const unsigned long nibs_to_mask[] = {";
	for (unsigned int i=0; i< BITS_IN_LONG + 1; ++i) {
		if (i % 2 == 0) {
			std::cout << "0x";
			std::cout << std::hex << bits_to_mask(i);
			if(i != 256)
				std::cout << ", ";
		}

	}
	std::cout << "};" << std::endl;
}
*/

const unsigned long nibs_to_mask[] = {0x0, 0xc000000000000000, 0xf000000000000000, 0xfc00000000000000, 0xff00000000000000, 0xffc0000000000000, 0xfff0000000000000, 0xfffc000000000000, 0xffff000000000000, 0xffffc00000000000, 0xfffff00000000000, 0xfffffc0000000000, 0xffffff0000000000, 0xffffffc000000000, 0xfffffff000000000, 0xfffffffc00000000, 0xffffffff00000000, 0xffffffffc0000000, 0xfffffffff0000000, 0xfffffffffc000000, 0xffffffffff000000, 0xffffffffffc00000, 0xfffffffffff00000, 0xfffffffffffc0000, 0xffffffffffff0000, 0xffffffffffffc000, 0xfffffffffffff000, 0xfffffffffffffc00, 0xffffffffffffff00, 0xffffffffffffffc0, 0xfffffffffffffff0, 0xfffffffffffffffc, 0xffffffffffffffff, };

constexpr unsigned int NUCLEOTITES_PER_BLOCK = sizeof(unsigned long) * 8 / 2;

void bit_pack(unsigned long * & result, unsigned long & num_blocks,
	const std::string & genome) {

	num_blocks = genome.size() / NUCLEOTITES_PER_BLOCK;

	if (num_blocks * NUCLEOTITES_PER_BLOCK != genome.size()) {
		++num_blocks;
	}

	result = (unsigned long*)calloc(num_blocks, sizeof(unsigned long));

	unsigned long i = 0;

	for (unsigned long block=0; block<num_blocks-1; ++block) {
		unsigned long next_block = 0;
		for (unsigned char j=0; j<NUCLEOTITES_PER_BLOCK; ++j, ++i) {
			next_block <<= 2;

			next_block |= nuc_to_code[ genome[i] ];
		}
		result[block] = next_block;
	}

	// this loop is the inner body of the last itteration of the above loop
	unsigned long next_block = 0;
	for (unsigned char j=0; j<NUCLEOTITES_PER_BLOCK; ++j, ++i) {
		next_block <<= 2;

		if (i < genome.size()) {
			next_block |= nuc_to_code[ genome[i] ];
		}
	}
	result[num_blocks-1] = next_block;
}

void left_shift_bitpacked_string(unsigned long * & genome, unsigned long & num_blocks) {
	unsigned long carry_cur = 0, carry_pre = 0;
	for(long long i=num_blocks-1; i>=0; --i){
		carry_cur = genome[i] & nibs_to_mask[1];	//keep highest 2 bits
		genome[i] <<= 2;
		genome[i] |= (carry_pre >> (sizeof(unsigned long) * 8 - 2));	//shift highest 2 bits to be lowest 2 bits, append
		carry_pre = carry_cur;
	}
}

void print_bitpacked_string(unsigned long* genome, unsigned long & num_blocks) {
	for (unsigned long block=0; block<num_blocks; ++block) {
		std::cout << std::hex << genome[block];
	}
	std::cout << std::endl;
}

std::vector<std::vector<unsigned long>> searcch_genome_for_shorts(
	unsigned long * & genome,
	unsigned long & genome_length,
	unsigned long & num_blocks_in_genome,
	std::vector<unsigned long *> & short_reads,
	std::vector<unsigned long> & short_read_lengths,
	std::vector<unsigned long> & num_blocks_in_short_reads //not used, assuming 32 character sequence
) {
	unsigned long trailing = (genome_length % NUCLEOTITES_PER_BLOCK);
	if (trailing == 0) {
		trailing = NUCLEOTITES_PER_BLOCK;
	}
	std::vector<std::vector<unsigned long>> all_indices (short_reads.size(), std::vector<unsigned long>(0));

	for (unsigned long shifts=0; shifts<NUCLEOTITES_PER_BLOCK; ++shifts) {
		for (unsigned long i=0; i < num_blocks_in_genome - 1; ++i) {
			for (unsigned long j=0; j < short_reads.size(); ++j) {
				unsigned long read_length = short_read_lengths[j];
				unsigned long mask = nibs_to_mask[read_length];
				unsigned long compare_me = genome[i] & mask;

				if (compare_me == short_reads[j][0]) { //assumes 32 character sequence search max!
					unsigned long index = i * NUCLEOTITES_PER_BLOCK + shifts;
					all_indices[j].push_back(index);
				}
			}
		}

		/* peeled off last block, I'm sure this could be simplified a bit but it handles the ege case of a trailing short of the 00 coded character correctly */
		for (unsigned long j=0; j < short_reads.size(); ++j) {
			unsigned long read_length = short_read_lengths[j];
			long remaining = trailing - shifts;
			if (!remaining) {
				break;
			}
			if (read_length <= remaining) {
				unsigned long mask = nibs_to_mask[read_length];
				unsigned long compare_me = genome[num_blocks_in_genome - 1] & mask;
				if (compare_me == short_reads[j][0]) { //assumes 32 character sequence search max!
					unsigned long index = (num_blocks_in_genome - 1) * NUCLEOTITES_PER_BLOCK + shifts;
					if (index < genome_length - read_length + 1) {
						all_indices[j].push_back(index);
					}
				}
			}

		}

		left_shift_bitpacked_string(genome, num_blocks_in_genome);
	}

	return all_indices;
}

int main(int argc, char**argv) {
	Clock c;

	if (argc == 3) {

		std::string genome;
		unsigned long genome_length;
		unsigned long*packed_genome;
		unsigned long num_blocks_in_genome;
		std::vector<std::string> short_reads;
		std::vector<unsigned long> short_read_lengths;
		unsigned long*packed_short;
		unsigned long num_blocks_in_short;
		std::vector<unsigned long*> packed_shorts;
		std::vector<unsigned long> num_blocks_in_shorts;
		std::vector<std::vector<unsigned long>> all_indices;

		/* read genome */
		std::ifstream genome_fin(argv[1]);
		std::getline(genome_fin, genome);//assumes genome is single line!
		genome_fin.close();
		genome_length = genome.size();

		/* read short reads */
		std::string short_read;
		std::ifstream short_reads_fin(argv[2]);
		while(std::getline(short_reads_fin, short_read)) {
			short_reads.push_back(short_read);
			short_read_lengths.push_back(short_read.size());
		}
		short_reads_fin.close();

		/* bitpack genome */
		bit_pack(packed_genome, num_blocks_in_genome, genome);

		/* bitpack short reads */
		for(std::string short_read: short_reads) {
			bit_pack(packed_short, num_blocks_in_short, short_read);
			packed_shorts.push_back(packed_short);
			num_blocks_in_shorts.push_back(num_blocks_in_short);
		}

		/* search */
		all_indices = searcch_genome_for_shorts(
			packed_genome,
			genome_length,
			num_blocks_in_genome,
			packed_shorts,
			short_read_lengths,
			num_blocks_in_shorts
		);

		/* output */
		for(unsigned long i=0; i < packed_shorts.size(); ++i) {
			std::sort(all_indices[i].begin(), all_indices[i].end());
			std::cout << short_reads[i] << " ";
			for (unsigned long j: all_indices[i]) {
				std::cout << j << " ";
			}
			std::cout << std::endl;
		}
	} else {
		std::cerr << "usage find-short-reads <genome_path> <short_reads_path>"
		<< std::endl;
	}
	c.ptock();
	return 0;
}
