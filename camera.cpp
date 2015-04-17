#include "camera.hpp"
#include <math.h>

Camera::Camera(vec3 p, mat44 r, float fov, float aspect) : pos(p), rot(r),
	fov(fov), aspect(aspect) {
	updateTransform();
}

Camera::~Camera() {
}

ray Camera::ndcToRay(vec2 ndc) const {
	// Convert to screen space
	vec2 screenSpace = vec2((ndc.x() * 2)-1, (ndc.y() * 2)-1);

	// Correct for X distortion caused by aspect ratio
	vec3 camSpace = vec3(
			screenSpace.x() * tan(fov/2),
			screenSpace.y() * tan(fov/aspect * 0.5),
			-1);

	// Build the pre-transformation ray
	ray r(vec3(), camSpace);

	// Transform it into world space
	return r.xform(xform);
}

void Camera::updateTransform() {
	xform = rot * mat44::translate(-pos);
}
