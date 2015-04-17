#pragma once
#include "math.hpp"

struct ray {
	vec3 origin, dir;

	ray(vec3 o, vec3 d);

	vec3 operator()(double t);
	ray xform(const mat44& m);
};

struct aabb {
	vec3 min, max;

	aabb(vec3 a, vec3 b);

	bool operator()(vec3& pt);
	aabb xform(const mat44& m);
};
