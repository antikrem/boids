#ifndef __SPACE__
#define __SPACE__

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

	// Fixed state update
	void cycle() {
		for (auto& i : boids) {
			i.doBoid(boids);
		}
		for (auto& i : boids) {
			i.update(size);
		}
	}

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