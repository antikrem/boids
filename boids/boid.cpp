#include "boid.h"

std::ostream& operator<<(std::ostream& os, const Boid& boid) {
	os << "(" << boid.position.x << "," << boid.position.y << "," << boid.velocity.getAngle() << ") ";
	return os;
}
