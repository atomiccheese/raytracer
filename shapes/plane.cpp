#include "../shape.hpp"

Plane::Plane(const Material& m) {
	mat = m;
}

aabb Plane::_getAABB() const {
}

Intersection Plane::_trace(ray r) const {
	Intersection res;
	res.hit = false;
	double denom = vec3(0,1,0).dot(r.dir);
	if(denom > 1e-6) {
		double d = res.end = (-r.origin).dot(vec3(0,1,0)) / denom;
		if(d < 0) return res;
		res.hit = true;
		res.normal = vec3(0,1,0);
		res.start = res.end = d;
		res.shape = this;
		res.point = r(res.start);
	}
	return res;
}

bool Plane::globalTest() const {
	return true;
}
