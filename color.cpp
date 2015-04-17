#include "color.hpp"

color::color(v4f v) : parts(v) {
}

color::color() : parts{0,0,0,0} {
}

color::color(float r, float g, float b, float a) : parts{r,g,b,a} {
}

float color::r() { return parts[0]; }
float color::g() { return parts[1]; }
float color::b() { return parts[2]; }
float color::a() { return parts[3]; }
void color::setR(float val) { parts[0] = val; }
void color::setG(float val) { parts[1] = val; }
void color::setB(float val) { parts[2] = val; }
void color::setA(float val) { parts[3] = val; }

color color::operator*(const color& other) const {
	return color(other.parts * parts);
}

color color::blend(const color& prev) const {
	float sp3 = parts[3], somp3 = 1-parts[3];
	v4f p3 = {sp3,sp3,sp3,sp3,}, omp3 = {somp3,somp3,somp3,somp3};
	return color(parts * p3 + prev.parts * omp3);
}

color color::operator*(float n) const {
	return color(parts*n);
}

color color::operator+(const color& other) const {
	return color(other.parts + parts);
}

color operator*(double n, const color& c) {
	return c*n;
}

color color::clipped() const {
	v4f x = parts;
	if(x[0] > 1) x[0] = 1;
	if(x[0] < 0) x[0] = 0;
	if(x[1] > 1) x[1] = 1;
	if(x[1] < 0) x[1] = 0;
	if(x[2] > 1) x[2] = 1;
	if(x[2] < 0) x[2] = 0;
	if(x[3] > 1) x[3] = 1;
	if(x[3] < 0) x[3] = 0;
	return color(x);
}

void color::clip() {
	parts = this->clipped().parts;
}

uint32_t color::encode() const {
	uint8_t r = parts[0]*255;
	uint8_t g = parts[1]*255;
	uint8_t b = parts[2]*255;
	uint8_t a = parts[3]*255;
	//return (r << 24) | (g << 16) | (b << 8) | a;
	return (a << 24) | (r << 16) | (g << 8) | b;
}
