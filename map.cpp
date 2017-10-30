#include "./Clock.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

std::string random_string() {
	std::string res = "";
	const unsigned int len=32;
	for (unsigned char i=0; i<len; ++i)
		res += 'A' + (rand() % 26);

	return res;
}

int main() {
	srand(0);

	const unsigned long N = 100000;

	std::vector<std::string> all_objs;
	std::map<std::string, int> str_to_int;
	unsigned long sum = 0;
	std::string name = "";

	for (unsigned long i=0; i<N; ++i) {
		std::string name = random_string();
		all_objs.push_back(name);
		str_to_int[name] = rand();
	}

	std::sort(all_objs.begin(), all_objs.end());

	Clock c;

	for (unsigned long i=0; i<all_objs.size(); ++i) {
		name = all_objs[long(i)];
		if(name.at(0) != 'A') {
			break;
		}
		sum += str_to_int[name];
	}

	c.ptock();

	std::cout << "sum: " << sum << std::endl;
}
ff
