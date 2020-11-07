#ifndef __BOID__
#define __BOID__

#include <math.h> 
#include <iostream>

#include "point2.h"
#include "helper.h"
#include "boid_settings.h"
#include <vector>

#define EPSILON 0.0000001

/**
 * Represents a single boid
 */
class Boid {
	Point2 position;
	Point2 velocity;
	Point2 force;

public:
	/**
	 * Will assign a random velocity
	 */
	Boid(Point2 position) 
			: position(position) {
		velocity = Point2(3.0 * randDouble() - 2.0, 3.0 * randDouble() - 2.0);
		force = Point2(0, 0);
	}

	const Point2& getPosition() const {
		return position;
	}

	const Point2& getVelocity() const {
		return velocity;
	}

private:

	// Adds force such that current velocity faces towards vector
	void steerToAllignWith(const Point2& directionTo, double strength = 1) {
		Point2 direction = directionTo;

		double mag = directionTo.distanceTo({ 0,0 });

		direction -= velocity;

		direction = direction * mag * strength;
		direction.clamp(BoidSettings::STEER_CAP);


		force += direction;
	}

	// Adds force such that velocity faces towards target
	void steerToTarget(const Point2& target, double strength = 1) {
		Point2 toTarget = target - position;

		double mag = toTarget.distanceTo({ 0,0 });
		if (mag < EPSILON) {
			return;
		}

		toTarget = toTarget - velocity;
		toTarget.clamp(BoidSettings::STEER_CAP);
		toTarget = toTarget * strength;

		force += toTarget;
	}

	/**
	 * Applys seperation, moving away from nearby boids
	 */
	void seperation(const std::vector<Boid>& boids, double scatterFactor) {
		Point2 steer = Point2(0, 0);

		int count = 0;
		for (auto& i : boids) {
			double distance = i.position.distanceTo(position);

			// Ignore self and boids too far
			if (distance > EPSILON && distance < BoidSettings::SEPERATION_DISTANCE * scatterFactor) {
				count++;

				Point2 difference = position - i.position;
				difference.normalise();
				difference = difference * (1 / distance);
				steer += difference;
			}

		}

		// Apply the steer force 
		if (count > 0) {
			// Average steer
			steer = steer * (1 / (double)count);
			steerToAllignWith(steer, scatterFactor);
		}
		
	}

	/**
	 * Applys cohesion, moving this boid towards the local center
	 */
	void cohesion(const std::vector<Boid>& boids) {
		Point2 center = Point2(0, 0);
		int count = 0;

		for (auto& i : boids) {
			double distance = i.position.distanceTo(position);

			// Ignore self and boids too far
			if (distance > EPSILON && distance < BoidSettings::COHESION_DISTANCE) {
				center += i.position;
				count++;
			}

		}

		// If no local boids, leave
		if (!count) {
			return;
		}

		// Average to find center
		center = center * (1 / count);

		steerToTarget(center, 0.01);
	}

	/**
	 * Applys alignment, directing all movement to average of surounding
	 */
	void allignment(const std::vector<Boid>& boids) {
		Point2 steer = Point2(0, 0);
		int count = 0;

		for (auto& i : boids) {
			double distance = i.position.distanceTo(position);

			// Ignore self and boids too far
			if (distance > EPSILON && distance < BoidSettings::ALIGN_DISTANCE) {
				steer += i.velocity;
				count++;
			}

		}

		// If no local boids, leave
		if (!count) {
			return;
		}

		steerToAllignWith(steer, 0.1);
	}


public:

	// Applies the body of the boid application
	// Based on the vector of boids
	void doBoid(const std::vector<Boid>& boids, double scatterFactor) {
		seperation(boids, scatterFactor);
		cohesion(boids);
		allignment(boids);
	}

	// Updates boid position based on previous force
	void update(const Point2& size) {
		force = force * 0.5;
		velocity += force;
		velocity.clamp(BoidSettings::VELOCITY_CAP, BoidSettings::VELOCITY_MIN);

		position += velocity;

		// Wrap position
		position.x = fmod(position.x + size.x, size.x);
		position.y = fmod(position.y + size.y, size.y);

		force = { 0,0 };
	}

	// Outputs a boid in its current state for saving
	friend std::ostream& operator<<(std::ostream& os, const Boid& boid);
};

std::ostream& operator<<(std::ostream& os, const Boid& boid);


#endif