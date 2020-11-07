#include "point2.h"

#define USE_OPENMP

#include "space.h"

//#define USE_GRAPHICS

#ifdef USE_GRAPHICS
	#include "renderer.h"
#endif // USE_GRAPHICS

#include "tester.h"


#include <iostream>
#include <time.h> 

int main(int argc, char* argv[]) {
	srand((int)time(NULL));

	// Sets up rendering with Simple2D
#ifdef USE_GRAPHICS
	Space gspace({ 500.0, 500.0 });
	gspace.newBoids(50);
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