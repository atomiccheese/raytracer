#pragma once
#include "geometry.hpp"
#include "color.hpp"

enum ShadingModel {
	SHADE_PHONG,
	SHADE_PHONG_BLINN
};

struct ShadingInfo {
	vec3 normal; // Surface normal
	vec3 rayDir; // View direction
	color ambient; // Ambient color
};

struct Material {
	color specular, diffuse;

	// Shading model - interpolated using Phong Shading
	ShadingModel shader;
	double kDiffuse, kSpecular, kAmbient;

	double opacity;
	double reflectivity;
	double specReflect;

	// Get the color for a given light. This should be blended with
	// any reflected light as well
	color shade(const ShadingInfo& shadeInfo, vec3 lightDir, color lightColor) const;

	// Get the ambient color for a given scene
	color ambient(const ShadingInfo& shadeInfo) const;
};
