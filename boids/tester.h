#ifndef __TESTER__
#define __TESTER__

#include "space.h"
#include <chrono> 
#include <string>

#define TRIALS 20

class Tester {
private:
	// Space that is tested against
	Space space = Space(Point2( 0,0 ));

	// Runs a test with a give size and vector of sizes 
	// Returns vector of results in microseconds
	std::vector<long long int> runTrials(std::vector<int> counts, const Point2& size) {
		space = Space(size);

		std::vector<long long int> results;

		for (int count : counts) {
			space.clearBoids();
			space.newBoids(count);
			std::cout << "Running: " << count << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < TRIALS; i++) {
				space.cycle();
			}
			auto duration = 
					std::chrono::duration_cast<std::chrono::microseconds>(
							std::chrono::high_resolution_clock::now() - start
						);
			results.push_back(duration.count() / TRIALS);
		}

		return results;
	}

public:
	// Run tests with a standard list of counts
	void runStandardTests() {
		std::vector<int> tests = { 10, 50, 100, 500, 1000, 2000, 3000, 4000, 5000, 6000 };
		
		auto results = runTrials(tests, {500, 500});

		for (int i = 0; i < results.size(); i++) {
			std::cout << tests[i] << " " << results[i] << std::endl;
		}
	}

	// Run tests with a given list of parameters
	void runTests(int argc, char* argv[]) {
		std::vector<int> tests;

		for (int i = 1; i < argc; i++) {
			try {
				tests.push_back(
						stoi(std::string(argv[i]))
					);
			}
			catch (std::invalid_argument) {

			}
		}

		auto results = runTrials(tests, { 500, 500 });

		for (int i = 0; i < results.size(); i++) {
			std::cout << tests[i] << " " << results[i] << std::endl;
		}

	}
};

#endif