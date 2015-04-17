#include <stdio.h>
#include "render.hpp"
#include <cmath>
#include "shape.hpp"

Image::Image(int w, int h) : width(w), height(h) {
	pixels = new color[width*height];
}

Image::~Image() {
	delete[] pixels;
}

void Image::writeToRGBABuffer(void* buf) {
	uint8_t* b = (uint8_t*)buf;
	for(int i=0;i<(width*height);i++) {
		b[1] = (int)(pixels[i].r() * 255);
		b[2] = (int)(pixels[i].g() * 255);
		b[3] = (int)(pixels[i].b() * 255);
		b[0] = (int)(pixels[i].a() * 255);
		b += 4;
	}
}

Renderer::Renderer(ImageConfig cfg) : config(cfg) {
}

Image* Renderer::render(World* world, Chunk c) const {
	Image* res = new Image(c.maxX - c.minX, c.maxY - c.minY);
	for(int y=0;y<res->height;y++) {
		for(int x=0;x<res->width;x++) {
			float sx = (c.minX + x + 0.5) / (float)(config.width);
			float sy = (c.minY + y + 0.5) / (float)(config.height);
			res->pixels[x+(y*res->width)] = renderRay(world,
					config.view.ndcToRay(
						vec2(sx, sy)));
		}
	}

	return res;
}

color Renderer::renderRay(World* world, ray r) const {
	Intersection i = world->raycast(r);
	ShadingInfo shadeInfo;
	if(i.hit) {
		shadeInfo.normal = i.normal;
		shadeInfo.rayDir = -r.dir;
		shadeInfo.ambient = config.ambient;
		color c = i.shape->mat.ambient(shadeInfo);
		const std::vector<Light*>& lights = world->getLights();
		for(std::vector<Light*>::const_iterator l = lights.begin();l != lights.end();l++) {
			Light* light = *l;

			// Check light. We add a small component of the normal here to make sure
			// that the start point is outside the hit object
			ray lRay = light->getCast(i.point);
			Intersection lInter = world->raycast(lRay);
			if(lInter.hit && !light->isInfinitelyFarAway() &&
					(lInter.point - i.point).lengthSquared() > 0.0001) continue;

			// Compute shading
			c = c + i.shape->mat.shade(shadeInfo,
					-lRay.dir,
					light->getColor(lRay.dir));
		}

		// Return resulting color
		c.clip();
		return c;
	}
	return color(0,0,0,0);
}
