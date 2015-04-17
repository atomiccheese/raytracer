#pragma once
#include "geometry.hpp"

class Camera {
	vec3 pos;
	float fov;
	mat44 rot;
	float aspect;

	mat44 xform;

	void updateTransform();
public:
	Camera(vec3 p, mat44 r, float fov, float aspect);
	~Camera();

	virtual ray ndcToRay(vec2 pos) const;
};
