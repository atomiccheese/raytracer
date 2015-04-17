#include "../light.hpp"

PointLight::PointLight(vec3 pos, double intensity, color c) : pos(pos), intensity(intensity), Light(c) {
}

double PointLight::getIntensity(const vec3& incoming, const vec3& p) const {
	return intensity/(pos - p).lengthSquared();
}

ray PointLight::getCast(const vec3& v) const {
	return ray(pos, v - pos);
}

double PointLight::getDistanceFrom(const vec3& pt) const {
	return (pt - pos).length();
}
