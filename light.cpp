#include "light.hpp"

Light::Light(const color& c) : col(c) {
}

color Light::getColor(const vec3& incoming) const {
	return col;
}

bool Light::isInfinitelyFarAway() {
	return false;
}
