#pragma once
#include "color.hpp"
#include "geometry.hpp"
#include "camera.hpp"
#include "world.hpp"

struct Chunk {
	int minX, minY;
	int maxX, maxY;
};

struct ImageConfig {
	int width, height;
	int depthLimit; // Maximum reflections a ray can undergo
	Camera view;
	color ambient;
};

struct Image {
	color* pixels;
	int width;
	int height;

	Image(int w, int h);
	~Image();

	void writeToRGBABuffer(void* buf);
};

class Renderer {
	ImageConfig config;
public:
	Renderer(ImageConfig cfg); 

	Image* render(World* world, Chunk c) const;
private:
	color renderRay(World* world, ray r) const;
};
