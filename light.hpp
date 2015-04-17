#pragma once
#include "math.hpp"
#include "color.hpp"
#include "geometry.hpp"

class Light {
protected:
	color col;
public:
	Light(const color& c);

	virtual color getColor(const vec3& incoming) const;
	virtual double getIntensity(const vec3& incoming, const vec3& pos) const=0;
	
	// Given a position, return the direction vector to raycast from to check
	// if the point can see this light
	virtual ray getCast(const vec3& v) const=0;

	// Return whether the light is at infinite distance
	virtual bool isInfinitelyFarAway();

	// Return the distance from a point, for intersection testing
	virtual double getDistanceFrom(const vec3& pt) const=0;
};

#include "lights/point.hpp"
