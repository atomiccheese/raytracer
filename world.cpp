#include "world.hpp"

World::World() {
}

World::~World() {
	for(std::vector<Shape*>::iterator i=m_shapes.begin();i != m_shapes.end();i++)
		delete *i;
	for(std::vector<Light*>::iterator i=m_lights.begin();i != m_lights.end();i++)
		delete *i;
}

Intersection World::raycast(ray r) {
	std::vector<Shape*>::iterator i;
	Intersection best;
	best.hit = false;
	for(i=m_shapes.begin();i != m_shapes.end();i++) {
		Intersection sect = (*i)->trace(r);
		if(sect.hit) {
			if(best.hit == false) best = sect;
			else if(best.start > sect.start) best = sect;
		}
	}
	return best;
}

const std::vector<Light*>& World::getLights() {
	return m_lights;
}

void World::addShape(Shape* s) {
	m_shapes.push_back(s);
}

void World::addLight(Light* l) {
	m_lights.push_back(l);
}
