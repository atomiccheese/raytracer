#pragma once

class Plane : public Shape {
public:
	Plane(const Material& m);

	bool globalTest() const;
protected:
	aabb _getAABB() const;
	Intersection _trace(ray r) const;
};
