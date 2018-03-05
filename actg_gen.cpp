#include <iostream>

int nucleotide_code(char nuc) {
	if(nuc == 'G')
		return 0;
	if(nuc == 'A')
		return 1;
	if(nuc == 'T')
		return 2;
	if(nuc == 'C')
		return 3;
	return -1;
}

int main() {
	std::cout << "const unsigned char nuc_to_code[] = {";
	for(unsigned int i=0; i<256; ++i) {
		std::cout << int((unsigned char)(nucleotide_code(char(i))));
		if(i != 255)
			std::cout << ", ";
	}
	std::cout << "};" << std::endl;

	return 0;
}
