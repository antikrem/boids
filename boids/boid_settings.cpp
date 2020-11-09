#include "boid_settings.h"

const double BoidSettings::VELOCITY_CAP = 4.0;
const double BoidSettings::VELOCITY_MIN = 3.0;
const double BoidSettings::STEER_CAP = 2;

const double BoidSettings::SEPERATION_DISTANCE = 20.0;
const double BoidSettings::ALIGN_DISTANCE = 50.0;
const double BoidSettings::COHESION_DISTANCE = 50.0;

const double BoidSettings::SEPERATION_FACTOR = 1;
const double BoidSettings::ALIGN_FACTOR = 0.1;
const double BoidSettings::COHESION_FACTOR = 0.001;