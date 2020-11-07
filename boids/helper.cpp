#include "helper.h"

double randDouble() {
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

int lazyStoi(std::string input) {
	int value = -1;
	try {
		value = stoi(input);
	}
	catch (const std::invalid_argument&) {

	}
	return value;
}