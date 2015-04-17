#pragma once
#include "geometry.hpp"
#include "material.hpp"

class Shape;
struct Intersection {
	double start, end;
	vec3 point;
	bool hit;
	vec3 normal;
	const Shape* shape;
};

class World;
class Shape {
protected:
	mat44 transform;
	mat44 itransform;
public:
	Material mat;

	Intersection trace(ray r) const;
	aabb getAABB() const;
	virtual bool globalTest() const;

	void setWorld(World* w);

	// Returns pointers for each construction chaining
	Shape* xform(const mat44& m);
	Shape* translate(const vec3& v);
	Shape* rotate(const vec3& v, double ang);

	void setXform(mat44 m);

protected:
	virtual Intersection _trace(ray r) const=0;
	virtual aabb _getAABB() const=0;

	World* m_world;
};

#include "shapes/sphere.hpp"
#include "shapes/plane.hpp"
