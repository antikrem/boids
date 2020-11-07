#include "point2.h"

std::ostream& operator<<(std::ostream& os, const Point2& point)
{
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}
