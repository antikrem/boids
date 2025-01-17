#ifndef __PARAMETERS__
#define __PARAMETERS__

#include <string> 
#include <vector>

#include <fstream>

#include "helper.h"

#include <iostream>

// Parses arguments
class Parameters {
public:
	int numberOfThreads = 1;
	int frames = 20;

	std::vector<int> counts = { 100 };
	int count = 0;
	Point2 size = Point2(500, 500);

	bool output = false;
	std::string outputFile = "results.txt";
	std::ofstream* outputStream = nullptr;

	int firstScatterCycle = 1300;
	int scatterDuration = 180;
	int totalScatterDuration = firstScatterCycle + scatterDuration;

	int seed = -1;

	Parameters() {

	}

	Parameters(int argc, char* argv[]) {
		for (int i = 1; i < argc; i++) {
			std::string parameter = std::string(argv[i]);

			if (parameter == "-counts") {
				counts.clear();

				i++;
				parameter = std::string(argv[i]);
				while (parameter.size() > 0) {
					if (parameter[0] == '-') {
						i--;
						break;
					}

					int value = lazyStoi(parameter);
					if (value > 0) {
						counts.push_back(value);
					}

					i++;
					if (i >= argc) {
						break;
					}				
					parameter = std::string(argv[i]);
				}
			}
			else if (parameter == "-save") {
				output = true;
				outputFile = std::string(argv[i + 1]);
				i++;
			}
			else if (parameter == "-threads") {
				numberOfThreads = lazyStoi(argv[i + 1]);
				i++;
			}
			else if (parameter == "-frames") {
				frames = lazyStoi(argv[i + 1]);
				i++;
			}
			else if (parameter == "-size") {
				size.x = lazyStoi(argv[i + 1]);
				size.y = lazyStoi(argv[i + 2]);
				i+=2;
			}
			else if (parameter == "-scatterstart") {
				firstScatterCycle = lazyStoi(argv[i + 1]);
				i++;

				totalScatterDuration = firstScatterCycle + scatterDuration;
			}
			else if (parameter == "-scatterduration") {
				scatterDuration = lazyStoi(argv[i + 1]);
				i++;

				totalScatterDuration = firstScatterCycle + scatterDuration;
			}
			else if (parameter == "-seed") {
				seed = lazyStoi(argv[i + 1]);
				i++;
			}
		}

		count = counts[0];
	}
};


#endif