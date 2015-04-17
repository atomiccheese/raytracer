#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "SDL.h"
#include "render.hpp"
#include "shape.hpp"

#define WORKER_THREADS 3
#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32
#define WIDTH 800
#define HEIGHT 600

#define FAIL(s, args...) do {\
	fprintf(stderr, s, ##args);\
	exit(1);\
	} while(0)

Renderer* buildRenderer(ImageConfig c) {
	return new Renderer(c);
}

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_VIDEO);

	// Init windowing
	SDL_Window* window = SDL_CreateWindow("raytracer",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT,
			0);
	if(window == NULL) FAIL("Cannot initialize SDL\n");

	// Set up rendering
	SDL_Renderer* render = SDL_CreateRenderer(
			window, -1, SDL_RENDERER_PRESENTVSYNC);
	if(render == NULL) FAIL("Cannot set up rendering\n");
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
	SDL_Texture *mainTex = SDL_CreateTexture(
			render,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH, HEIGHT);

	// Split into subzones. Create chunk structures for each sub-area.
	int chunksX = ceil((float)WIDTH/(float)CHUNK_WIDTH);
	int chunksY = ceil((float)HEIGHT/(float)CHUNK_HEIGHT);
	Chunk chunks[chunksX*chunksY];
	int cx = 0;
	int nextCx = CHUNK_WIDTH;
	for(int x=0;x<chunksX;x++) {
		int cy = 0;
		int nextCy = CHUNK_HEIGHT;
		for(int y=0;y<chunksY;y++) {
			Chunk& c = chunks[x+(y*chunksX)];
			c.minX = cx;
			c.minY = cy;
			c.maxX = nextCx;
			c.maxY = nextCy;
			cy = nextCy;
			nextCy += CHUNK_HEIGHT;
			if(nextCy >= HEIGHT) nextCy = HEIGHT-1;
		}
		cx = nextCx;
		nextCx += CHUNK_WIDTH;
		if(nextCx >= WIDTH) nextCx = WIDTH-1;
	}

	// Now that we've split into subzones, render each subzone
	Camera cam(vec3(0,0,20), mat44::rotate(vec3(0,1,0), 0),
			PI/4, ((float)WIDTH)/HEIGHT);
	World* world = new World();

	Material red;
	red.specular = color(1,1,1,1);
	red.diffuse = color(1,0,0,1);
	red.shader = SHADE_PHONG;
	red.opacity = 1;
	red.reflectivity = 0;
	red.specReflect = 5;
	red.kDiffuse = 0.8;
	red.kSpecular = 0.4;
	red.kAmbient = 0.2;

	Material blue = red;
	blue.diffuse = color(0,0,1,1);
	blue.kDiffuse = 1;

	Material white = blue;
	white.kAmbient = 100;
	white.kSpecular = 0;
	white.kDiffuse = 0;

	world->addShape((new Plane(blue))->translate(vec3(0,5,0)));
	world->addShape(new Sphere(2.5, red));
	world->addShape((new Sphere(3, blue))->translate(vec3(5,2,0)));

	//world->addShape((new Sphere(0.1, white))->translate(vec3(8,-5,10)));
	world->addLight(new PointLight(vec3(10,5,10), 5));
	world->addLight(new PointLight(vec3(-10,5,-5), 5));

	Renderer* r = buildRenderer({WIDTH, HEIGHT, 8, cam, color(0.1,0.1,0.1,0)});
	Image* zones[chunksX*chunksY];
	uint8_t *buffer = (uint8_t*)malloc(chunksX*chunksY*CHUNK_WIDTH*CHUNK_HEIGHT*4);

	for(int i=0;i<(chunksX*chunksY);i++) {
		// Draw the chunk
		zones[i] = r->render(world, chunks[i]);

		// Blit it into the scene
		zones[i]->writeToRGBABuffer(buffer);
		SDL_Rect blitRect;
		blitRect.x = chunks[i].minX;	blitRect.y = chunks[i].minY;
		blitRect.w = zones[i]->width;	blitRect.h = zones[i]->height;

		SDL_UpdateTexture(mainTex, &blitRect, (void*)buffer,
				zones[i]->width*4);
		SDL_RenderClear(render);
		SDL_RenderCopy(render, mainTex, NULL, NULL);
		SDL_RenderPresent(render);
	}

	SDL_Delay(5000);
	SDL_Quit();

	return 0;
}
