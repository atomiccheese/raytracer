#include "geometry.hpp"

ray::ray(vec3 o, vec3 d) : origin(o), dir(d.normalized()) {
}

vec3 ray::operator()(double t) {
	return origin+(dir*t);
}

ray ray::xform(const mat44& m) {
	vec3 sample = origin + dir;
	vec3 newSample = m * sample;
	vec3 newOrigin = m * origin;
	return ray(newOrigin, (newSample - newOrigin).normalized());
}

aabb::aabb(vec3 a, vec3 b) {
	min.x() = (a.x() < b.x()) ? a.x() : b.x();
	min.y() = (a.y() < b.y()) ? a.y() : b.y();
	min.z() = (a.z() < b.z()) ? a.z() : b.z();

	max.x() = (a.x() > b.x()) ? a.x() : b.x();
	max.y() = (a.y() > b.y()) ? a.y() : b.y();
	max.z() = (a.z() > b.z()) ? a.z() : b.z();
}

bool aabb::operator()(vec3& pt) {
	return (pt.x() <= max.x() && pt.x() >= min.x()) &&
		(pt.y() <= max.y() && pt.y() >= min.y()) &&
		(pt.z() <= max.z() && pt.z() >= min.z());
}

aabb aabb::xform(const mat44& m) {
	return aabb(m*min, m*max);
}
