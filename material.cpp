#include "material.hpp"
#include <stdio.h>
#include <math.h>

color Material::shade(const ShadingInfo& shadeInfo, vec3 lightDir, color lightColor) const {
	switch(shader) {
	case SHADE_PHONG:
	case SHADE_PHONG_BLINN: // TODO: Actually implement Phong-Blinn shading
	{
		color c(0,0,0,0);
		vec3 R = 2*lightDir.dot(shadeInfo.normal)*shadeInfo.normal - lightDir;
		R.normalize();
		double diffTerm = lightDir.dot(shadeInfo.normal);
		double specTerm = R.dot(shadeInfo.rayDir);
		if(diffTerm > 0) c = c + (kDiffuse * diffTerm * diffuse);
		if(diffTerm > 0 && specTerm > 0) c = c + (kSpecular * pow(specTerm, specReflect) * specular);
		return c * lightColor;
	}; break;
	}
}

color Material::ambient(const ShadingInfo& shadeInfo) const {
	return (kAmbient * shadeInfo.ambient);
}
