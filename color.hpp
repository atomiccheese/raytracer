#pragma once
#include <stdint.h>
typedef float v4f __attribute__((vector_size(16)));

class color {
	v4f parts;
	color(v4f v);
public:
	color();
	color(float r, float g, float b, float a=1);

	float r();
	float g();
	float b();
	float a();
	void setR(float val);
	void setG(float val);
	void setB(float val);
	void setA(float val);
	color operator*(const color& other) const;
	color operator*(float n) const;
	color operator+(const color& other) const;
	color clipped() const;
	void clip();
	uint32_t encode() const;

	color blend(const color& prev) const;
};

color operator*(double n, const color& c);
