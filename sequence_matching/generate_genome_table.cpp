#include <iostream>

int nucleotide_code(char nuc) {
	if (nuc  == 'G') //00
		return 0;
	if (nuc == 'A') //01
		return 1;
	if (nuc == 'T') //10
		return 2;
	if (nuc == 'C') //11
		return 3;
	return -1;
}

int main() {
	std::cout << "const unsigned char nuc_to_code[] = {";
	for (unsigned int i=0; i<256; ++i) {
		std::cout << int((unsigned char) nucleotide_code(char(i)));
		if(i != 256)
			std::cout << ", ";
	}
	std::cout << "};" << std::endl;
}
