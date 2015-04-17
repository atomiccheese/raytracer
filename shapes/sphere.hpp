#pragma once

class Sphere : public Shape {
	double rad;
public:
	Sphere(double r, Material m);

protected:
	aabb _getAABB() const;
	Intersection _trace(ray r) const;
};
