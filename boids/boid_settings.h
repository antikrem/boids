#ifndef __BOID_SETTINGS__
#define __BOID_SETTINGS__

struct BoidSettings {
	static const double VELOCITY_CAP;
	static const double VELOCITY_MIN;
	static const double STEER_CAP;

	static const double SEPERATION_DISTANCE;
	static const double ALIGN_DISTANCE;
	static const double COHESION_DISTANCE;

	static const double SEPERATION_FACTOR;
	static const double ALIGN_FACTOR;
	static const double COHESION_FACTOR;
};

#endif