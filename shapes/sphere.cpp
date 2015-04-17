#include "../shape.hpp"
#include <cmath>

Sphere::Sphere(double r, Material m) :
	rad(r) {
	mat = m;
}

aabb Sphere::_getAABB() const {
	return aabb(vec3(-rad,-rad,-rad), vec3(rad,rad,rad));
}

Intersection Sphere::_trace(ray r) const {
	Intersection res;
	res.hit = false;

	double a = r.dir.dot(r.dir);
	double b = 2*r.dir.dot(r.origin);
	double c = r.origin.dot(r.origin) - (rad*rad);

	double discrim = b*b - 4*a*c;
	if(discrim < 0) return res;
	res.hit = true;
	double t0 = (-b - sqrt(discrim))/(2*a);
	double t1 = (-b + sqrt(discrim))/(2*a);
	if(t0 < t1) {
		res.start = t0;
		res.end = t1;
	} else {
		res.end = t1;
		res.start = t0;
	}
	res.point = r(res.start);
	res.normal = res.point.normalized();
	res.shape = this;
	return res;
}
