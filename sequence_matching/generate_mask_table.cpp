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
