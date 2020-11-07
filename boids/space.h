#ifndef __SPACE__
#define __SPACE__

#ifdef USE_OPENMP

#include <omp.h>

#endif

#include "point2.h"
#include "boid.h"

#include <vector>

class Space {
	Point2 size;
	std::vector<Boid> boids;

public:
	Space(Point2 size) 
			: size(size) {
	}

	const Point2& getSize() const {
		return size;
	}

#ifdef USE_OPENMP

	// Fixed state update
	void cycle(int threadCount = 1) {
		#pragma omp parallel num_threads(5) 
		{
			std::cout << "hello " << omp_get_thread_num() << std::endl;
			#pragma omp for
			for (int i = 0; i < (int)boids.size(); i++) {
				boids[i].doBoid(boids);
			}
			#pragma omp for
			for (int i = 0; i < (int)boids.size(); i++) {
				boids[i].update(size);
			}
		}
	}

#else

	// Fixed state update
	void cycle(int threadCount = 1) {
		for (auto& i : boids) {
			i.doBoid(boids);
		}
		for (auto& i : boids) {
			i.update(size);
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