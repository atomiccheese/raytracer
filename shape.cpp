#include "shape.hpp"

void Shape::setWorld(World* w) {
	m_world = w;
}

Intersection Shape::trace(ray r) const {
	Intersection is = _trace(r.xform(itransform));
	if(is.hit) {
		is.point = transform * is.point;
		is.normal = ((transform * is.normal) - (transform * vec3())).normalized();
	}
	return is;
}


aabb Shape::getAABB() const {
	return _getAABB().xform(transform);
}

Shape* Shape::xform(const mat44& m) {
	transform = transform * m;
	itransform = transform.inverse();
	return this;
}

Shape* Shape::translate(const vec3& v) {
	return xform(mat44::translate(v));
}

Shape* Shape::rotate(const vec3& v, double ang) {
	return xform(mat44::rotate(v, ang));
}

void Shape::setXform(mat44 m) {
	transform = m;
	itransform = m.inverse();
}

bool Shape::globalTest() const {
	return false;
}
