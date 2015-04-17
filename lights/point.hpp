#pragma once

class PointLight : public Light {
	vec3 pos;
	double intensity;
public:
	PointLight(vec3 pos, double intensity, color c=color(1,1,1,1));
	
	double getIntensity(const vec3& incoming, const vec3& pos) const;
	ray getCast(const vec3& v) const;
	double getDistanceFrom(const vec3& pt) const;
};
