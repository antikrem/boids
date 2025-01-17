#ifndef __SPACE__
#define __SPACE__

#ifdef USE_OPENMP

#include <omp.h>

#endif

#include "point2.h"
#include "boid.h"
#include "parameters.h"

#include <vector>
#include <algorithm> 

class Space {
	Point2 size;
	std::vector<Boid> boids;

	// Writes all boids to output file
	void writeToFile(Parameters& parameters) {
		for (auto& boid : boids) {
			(*parameters.outputStream) << boid;
		}

		(*parameters.outputStream) << '\n';
	}


public:
	Space(Point2 size) 
			: size(size) {
	}

	const Point2& getSize() const {
		return size;
	}

#ifdef USE_OPENMP

	// Fixed state update
	void cycle(Parameters& parameter, int cycle) {
		bool firstScatter = (cycle % parameter.totalScatterDuration == parameter.firstScatterCycle);
		bool scatter = (cycle % parameter.totalScatterDuration >= parameter.firstScatterCycle);

		if (parameter.output) {
			writeToFile(parameter);
		}

		#pragma omp parallel num_threads(parameter.numberOfThreads) 
		{
			#pragma omp for
			for (int i = 0; i < (int)boids.size(); i++) {
				boids[i].doBoid(boids);
			}
			#pragma omp for
			for (int i = 0; i < (int)boids.size(); i++) {
				boids[i].update(parameter, i, firstScatter, scatter);
			}
		}
	}

	// Multiple cycle update
	void multiCycle(Parameters& parameter) {
		#pragma omp parallel num_threads(parameter.numberOfThreads) 
		{
			// Set parameters to work out where to do work
			int threadNumber = omp_get_thread_num();
			int threadCount = omp_get_num_threads();
			int width = (int)std::ceil((double)parameter.count / threadCount);
			int start = threadNumber * width;
			int end = std::min(width * (threadNumber + 1), parameter.count);

			for (int cycle = 0; cycle < parameter.frames; cycle++) {

				if (parameter.output) {
					#pragma omp barrier
					if (threadNumber == 0) {
						writeToFile(parameter);
					}
					#pragma omp barrier
					
				}

				bool firstScatter = (cycle % parameter.totalScatterDuration == parameter.firstScatterCycle);
				bool scatter = (cycle % parameter.totalScatterDuration >= parameter.firstScatterCycle);

				#pragma omp barrier

				for (int i = start; i < end; i++) {
					boids[i].doBoid(boids);
				}

				#pragma omp barrier

				for (int i = start; i < end; i++) {
					boids[i].update(parameter, i, firstScatter, scatter);
				}

			}

		}
	}

#else

	// Fixed state update
	void cycle(Parameters& parameter, int cycle) {
		bool firstScatter = (cycle % parameter.totalScatterDuration == parameter.firstScatterCycle);
		bool scatter = (cycle % parameter.totalScatterDuration >= parameter.firstScatterCycle);

		if (parameter.output) {
			writeToFile(parameter);
		}

		for (auto& i : boids) {
			i.doBoid(boids);
		}
		for (int i = 0; i < (int)boids.size(); i++) {
			boids[i].update(parameter, i, firstScatter, scatter);
		}
	}

	// Multiple cycle update
	void multiCycle(Parameters& parameter) {
		for (int i = 0; i < parameter.frames; i++) {
			cycle(parameter, i);
		}
	}

#endif

	/**
	* Spawns a random new boid
	*/
	void newBoid() {
		boids.push_back(
			Boid({ randDouble() * size.x, randDouble() * size.y })
		);
	}

	/**
	* Spawns many random new boids
	*/
	void newBoids(int count) {
		for (int i = 0; i < count; i++) {
			boids.push_back(
				Boid({ randDouble() * size.x, randDouble() * size.y })
			);
		}
	}

	/**
	* Clears all boids
	*/
	void clearBoids() {
		boids.clear();
	}

	const std::vector<Boid>& getBoids() const {
		return boids;
	}

};

#endif