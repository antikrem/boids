// #define USE_OPENMP

#include "space.h"

#define USE_GRAPHICS

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
	copySpace(gspace);
	setUpRenderer(gspace);

	// Otherwise run test
#else // USE_GRAPHICS

	Tester tests;
	if (argc > 1) {
		tests.runTests(argc, argv);
	}
	else {
		tests.runStandardTests();
	}

#endif // USE_GRAPHICS
}