#include "helper.h"

#include <stdexcept>

double randDouble() {
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

int lazyStoi(std::string input) {
	int value = -1;
	try {
		value = std::stoi(input);
	}
	catch (const std::invalid_argument&) {

	}
	return value;
}