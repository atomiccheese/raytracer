#pragma once
#include <vector>
#include "shape.hpp"
#include "light.hpp"

class World {
	std::vector<Shape*> m_shapes;
	std::vector<Light*> m_lights;
public:
	World();
	~World();

	Intersection raycast(ray r);
	const std::vector<Light*>& getLights();

	void addShape(Shape* s);
	void addLight(Light* l);
};
