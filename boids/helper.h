#ifndef __HELPER__
#define __HELPER__

#include <stdlib.h> 
#include <string>
#include <vector>

// Create a random double from 0 to 1
double randDouble();

// Lazy stoi, returns -1 on failure
int lazyStoi(std::string value);

#endif