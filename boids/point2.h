#ifndef __POINT2__
#define __POINT2__

#include <math.h>

#include <string>
#include <iostream>

#define PI 3.14159265358

class Point2 {

public:
	double x;
	double y;

	Point2() {
		this->x = 0;
		this->y = 0;
	}

	Point2(double v) {
		this->x = v;
		this->y = v;
	}

	Point2(double x, double y) {
		this->x = x;
		this->y = y;
	}

	static Point2 fromPolar(double mag, double angle) {
		return Point2(
			mag * std::cos(angle * 180 / PI),
			mag * std::sin(angle * 180 / PI)
		);
	}

	//sets polar part
	void set(double x, double y) {
		this->x = x;
		this->y = y;
	}

	Point2 operator+(const Point2& b) {
		return Point2(this->x + b.x, this->y + b.y);
	}

	void operator+=(const Point2& b) {
		this->x += b.x;
		this->y += b.y;
	}

	Point2 operator-(const Point2& b) const {
		return Point2(this->x - b.x, this->y - b.y);
	}

	void operator-=(const Point2& b) {
		this->x -= b.x;
		this->y -= b.y;
	}

	Point2 operator*(const double& b) {
		return Point2(b * this->x, b * this->y);
	}

	Point2 rotate(double rotation) {
		double magniute = distanceTo({ 0,0 });
		double angle = atan2(y, x);
		angle += (rotation * PI / 180);
		return Point2(magniute * cos(angle), magniute * sin(angle));
	}


	// Computes distance to another point
	double distanceTo(const Point2& point) const {
		return (double)sqrt(pow(point.x - this->x, 2) + pow(point.y - this->y, 2));
	}

	// Normalises this vector
	void normalise(double strength = 1.0f) {
		double mag = distanceTo({ 0,0 }) / strength;
		x = x / mag;
		y = y / mag;
	}

	// Clamps this to given strength
	void clamp(double max) {
		double mag = distanceTo({ 0,0 });
		if (mag > max) {
			normalise(max);
		}
	}

	// Clamps this to given strength with min
	void clamp(double max, double min) {
		double mag = distanceTo({ 0,0 });
		if (mag > max) {
			normalise(max);
		}
		if (mag < min) {
			normalise(min);
		}
	}

	// Returns angle value
	double getAngle() const {
		return atan2(y, x) * (180 / PI);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point2& point);
};

std::ostream& operator<<(std::ostream& os, const Point2& point);


#endif