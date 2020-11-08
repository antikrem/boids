// Uncomment the following lines for different compile options

#define USE_OPENMP

// #define USE_GRAPHICS

#include "space.h"

#ifdef USE_GRAPHICS
	#include "renderer.h"
#endif // USE_GRAPHICS

#include "tester.h"

#include <iostream>
#include <time.h> 

int main(int argc, char* argv[]) {
	srand((int)time(NULL));

	// Generate parameter object
	Parameters parameters(argc, argv);

	// Sets up rendering with Simple2D
#ifdef USE_GRAPHICS
	Space gspace(parameters.size);
	gspace.newBoids(parameters.counts[0]);
	copyEnvironment(gspace, parameters);
	setUpRenderer(gspace);

	// Otherwise run test
#else // USE_GRAPHICS

	Tester tests;
	tests.runTests(parameters);

#endif // USE_GRAPHICS
}