#ifndef __TESTER__
#define __TESTER__

#include "space.h"
#include <chrono> 
#include <string>

#include "parameters.h"

#define TRIALS 20

class Tester {
private:
	// Space that is tested against
	Space space = Space(Point2( 0,0 ));

	// Runs a test with a give size and vector of sizes 
	// Returns vector of results in microseconds
	std::vector<long long int> runTrials(const Parameters& parameters) {
		space = Space(parameters.size);

		std::vector<long long int> results;

		for (int count : parameters.counts) {
			space.clearBoids();
			space.newBoids(count);
			std::cout << "Running: " << count << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < parameters.frames; i++) {
				space.cycle(parameters.numberOfThreads);
			}
			auto duration = 
					std::chrono::duration_cast<std::chrono::microseconds>(
							std::chrono::high_resolution_clock::now() - start
						);
			results.push_back(duration.count() / parameters.frames);
		}

		return results;
	}

public:
	// Run tests with a given list of parameters
	void runTests(const Parameters& parameters) {

		auto results = runTrials(parameters);

		for (int i = 0; i < (int)results.size(); i++) {
			std::cout << parameters.counts[i] << " " << results[i] << std::endl;
		}

	}
};

#endif