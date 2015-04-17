#include "math.hpp"
#include <cmath>

vec2::vec2(v2sd v) : value(v) {
}

vec2::vec2() : value{0,0} {
}

vec2::vec2(double vx, double vy) : value{vx,vy} {
}

double& vec2::x() {
	return value[0];
}

double& vec2::y() {
	return value[1];
}

double vec2::gx() const {
	return value[0];
}

double vec2::gy() const {
	return value[1];
}

vec2 vec2::operator+(const vec2& v) const {
	return vec2(v.value + value);
}

vec2 vec2::operator-() const {
	return vec2(-value);
}

vec2 vec2::operator-(const vec2& v) const {
	return vec2(value - v.value);
}

vec2 vec2::operator*(double n) const {
	return vec2(value * n);
}

vec2 vec2::operator/(double n) const {
	return vec2(value / n);
}

vec2& vec2::operator+=(const vec2& v) {
	value += v.value;
	return *this;
}

vec2& vec2::operator-=(const vec2& v) {
	value -= v.value;
	return *this;
}

vec2& vec2::operator*=(double n) {
	value *= n;
	return *this;
}

vec2& vec2::operator/=(double n) {
	value /= n;
	return *this;
}

bool vec2::operator==(const vec2& v) const {
	return (value[0] == v.value[0] && value[1] == v.value[1]);
}

bool vec2::operator!=(const vec2& v) const {
	return (value[0] != v.value[0] || value[1] != v.value[1]);
}

double vec2::lengthSquared() const {
	v2sd v = value*value;
	return v[0]+v[1];
}

double vec2::length() const {
	return sqrt(lengthSquared());
}

vec2& vec2::normalize() {
	(*this) /= length();
	return *this;
}

vec2 vec2::normalized() const {
	return (*this) / length();
}

double vec2::dot(const vec2& other) const {
	v2sd v = value*other.value;
	return v[0]+v[1];
}

vec3::vec3(v4sd v) : value(v) {
}

vec3::vec3() : value{0,0,0,0} {
}

vec3::vec3(double x, double y, double z) : value{x,y,z,0} {
}

double& vec3::x() {
	return value[0];
}

double& vec3::y() {
	return value[1];
}

double& vec3::z() {
	return value[2];
}

double vec3::gx() const {
	return value[0];
}

double vec3::gy() const {
	return value[1];
}

double vec3::gz() const {
	return value[2];
}

vec3 vec3::operator+(const vec3& v) const {
	return vec3(v.value + value);
}

vec3 vec3::operator-() const {
	return vec3(-value);
}

vec3 vec3::operator-(const vec3& v) const {
	return vec3(value - v.value);
}

vec3 vec3::operator*(double n) const {
	return vec3(value * n);
}

vec3 vec3::operator/(double n) const {
	return vec3(value / n);
}

vec3& vec3::operator+=(const vec3& v) {
	value += v.value;
	return *this;
}

vec3& vec3::operator-=(const vec3& v) {
	value -= v.value;
	return *this;
}

vec3& vec3::operator*=(double n) {
	value *= n;
	return *this;
}

vec3& vec3::operator/=(double n) {
	value /= n;
	return *this;
}

bool vec3::operator==(const vec3& v) const {
	return (value[0] == v.value[0] && value[1] == v.value[1] && value[2] == v.value[2]);
}

bool vec3::operator!=(const vec3& v) const {
	return (value[0] != v.value[0] || value[1] != v.value[1] || value[2] != v.value[2]);
}

double vec3::lengthSquared() const {
	v4sd v = value * value;
	return v[0] + v[1] + v[2];
}

double vec3::length() const {
	return sqrt(lengthSquared());
}

vec3& vec3::normalize() {
	value /= length();
	return *this;
}

vec3 vec3::normalized() const {
	return vec3(value / length());
}

// Use long since sizeof(int type) must equal sizeof(double)
typedef long v4sl __attribute__((vector_size(32)));

vec3 vec3::cross(const vec3& v) const {
	v4sl a = {1,2,0,3};
	v4sl b = {2,0,1,3};
	return vec3(
		(__builtin_shuffle(value, a) *
		 __builtin_shuffle(v.value, b)) -
		(__builtin_shuffle(value, b) *
		 __builtin_shuffle(v.value, a)));
}

double vec3::dot(const vec3& v) const {
	v4sd n = v.value * value;
	return n[0] + n[1] + n[2];
}

mat22::mat22(v4sd v) : value(v) {
}

mat22::mat22() : value{1,0,0,1} {
}

mat22::mat22(double a[]) : value{a[0], a[1], a[2], a[3]} {
}

mat22::mat22(double ang) : value{cos(ang), -sin(ang), sin(ang), cos(ang)} {
}

double& mat22::a() { return value[0]; }
double& mat22::b() { return value[1]; }
double& mat22::c() { return value[2]; }
double& mat22::d() { return value[3]; }

mat22 mat22::operator+(const mat22& m) const {
	return mat22(value + m.value);
}

mat22 mat22::operator-(const mat22& m) const {
	return mat22(value - m.value);
}

mat22 mat22::operator*(const mat22& m) const {
	// | a1 b1 | * | a2 b2 | = | a1*a2 + b1*c2 a1*b2 + b1*d2 |
	// | c1 d1 |   | c2 d2 |   | c1*a2 + d1*c2 c1*b2 + d1*d1 |
	v4sl fcA = {0,0,2,2}, scA = {1,1,3,3};
	v4sl fcB = {0,1,0,1}, scB = {2,3,2,3};
	v4sd fstComponent =
		__builtin_shuffle(value, fcA) *
		__builtin_shuffle(m.value, fcB);
	v4sd sndComponent =
		__builtin_shuffle(value, scA) *
		__builtin_shuffle(m.value, scB);
	return mat22(fstComponent + sndComponent);
}

mat22 mat22::operator*(double n) const {
	return mat22(value * n);
}

double mat22::det() const {
	return value[0]*value[3] - value[1]*value[2];
}

mat22 mat22::inverse() const {
	v4sl transpose = {3,1,2,0}; // [D B] [C A]
	v4sd tmp = {1,-1,-1,1};
	return mat22((1/det()) *
		(__builtin_shuffle(value, transpose) * tmp));
}

mat44::mat44(v16sd v) : value(v) {
}

mat44::mat44() : value{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {
}

mat44::mat44(double v[]) : value{v[0], v[1], v[2], v[3],
	v[4], v[5], v[6], v[7],
	v[8], v[9], v[10], v[11],
	v[12], v[13], v[14], v[15]} {
}

double& mat44::operator[](int n) {
	return value[n];
}

mat44 mat44::operator+(const mat44& m) const {
	return mat44(value + m.value);
}

mat44 mat44::operator-(const mat44& m) const {
	return mat44(value - m.value);
}

typedef long v16sl __attribute__((vector_size(128)));

#define BITA(x) __builtin_shuffle(value, x)
#define BITB(x) __builtin_shuffle(m.value, x)
mat44 mat44::operator*(const mat44& m) const {
	v16sl	c1A = {0,0,0,0, 	4,4,4,4,	8,8,8,8,	12,12,12,12},
		c2A = {1,1,1,1, 	5,5,5,5,	9,9,9,9,	13,13,13,13},
		c3A = {2,2,2,2, 	6,6,6,6,	10,10,10,10,	14,14,14,14},
		c4A = {3,3,3,3, 	7,7,7,7,	11,11,11,11,	15,15,15,15},
		c1B = {0,1,2,3, 	0,1,2,3,	0,1,2,3,	0,1,2,3},
		c2B = {4,5,6,7, 	4,5,6,7,	4,5,6,7,	4,5,6,7},
		c3B = {8,9,10,11,	8,9,10,11,	8,9,10,11,	8,9,10,11},
		c4B = {12,13,14,15,	12,13,14,15,	12,13,14,15,	12,13,14,15};
	v16sd	a1 = BITA(c1A), b1 = BITB(c1B),
		a2 = BITA(c2A), b2 = BITB(c2B),
		a3 = BITA(c3A), b3 = BITB(c3B),
		a4 = BITA(c4A), b4 = BITB(c4B);
	v16sd	c1 = a1*b1,
		c2 = a2*b2,
		c3 = a3*b3,
		c4 = a4*b4;
	return mat44(c1+c2+c3+c4);
}
#undef BITA
#undef BITB

mat44 mat44::operator*(double n) const {
	return mat44(value * n);
}

mat44 mat44::translate(vec3 v) {
	mat44 m;
	m[3] = v.x();
	m[7] = v.y();
	m[11] = v.z();
	m[15] = 1;
	return m;
}

mat44 mat44::rotate(vec3 axis, double angle) {
	axis.normalize();
	mat44 m;
	double ca = cos(angle);
	double sa = sin(angle);
	m[0] =	ca + axis.x()*axis.x()*(1-ca);
	m[1] =	axis.x()*axis.y()*(1-ca) - axis.z()*sa;
	m[2] =	axis.x()*axis.z()*(1-ca) + axis.y()*sa;
	m[3] =	0;

	m[4] =	axis.x()*axis.y()*(1-ca) - axis.y()*sa;
	m[5] =	ca + axis.y()*axis.y()*(1-ca);
	m[6] =	axis.y()*axis.z()*(1-ca) - axis.x()*sa;
	m[7] =	0;

	m[8] =	axis.z()*axis.x()*(1-ca) - axis.y()*sa;
	m[9] =	axis.z()*axis.y()*(1-ca) + axis.x()*sa;
	m[10] =	ca + axis.z()*axis.z()*(1-ca);
	m[11] =	0;

	m[12] = m[13] = m[14] = m[15] = 0;
	return m;
}

double mat44::det() const {
	v16sd m;
	m[0] =	value[5] * value[10] * value[15] -
		value[5] * value[11] * value[14] -
		value[9] * value[6] * value[15] +
		value[9] * value[7] * value[14] +
		value[13] * value[6] * value[11] -
		value[13] * value[7] * value[10];
	m[4] =	-value[4]  * value[10] * value[15] + 
		value[4]  * value[11] * value[14] + 
		value[8]  * value[6]  * value[15] - 
		value[8]  * value[7]  * value[14] - 
		value[12] * value[6]  * value[11] + 
		value[12] * value[7]  * value[10];
	m[8] =	value[4]  * value[9] * value[15] - 
		value[4]  * value[11] * value[13] - 
		value[8]  * value[5] * value[15] + 
		value[8]  * value[7] * value[13] + 
		value[12] * value[5] * value[11] - 
		value[12] * value[7] * value[9];
	m[12] =	-value[4]  * value[9] * value[14] + 
		value[4]  * value[10] * value[13] +
		value[8]  * value[5] * value[14] - 
		value[8]  * value[6] * value[13] - 
		value[12] * value[5] * value[10] + 
		value[12] * value[6] * value[9];
	m[1] =	-value[1]  * value[10] * value[15] + 
		value[1]  * value[11] * value[14] + 
		value[9]  * value[2] * value[15] - 
		value[9]  * value[3] * value[14] - 
		value[13] * value[2] * value[11] + 
		value[13] * value[3] * value[10];
	m[5] =	value[0]  * value[10] * value[15] - 
		value[0]  * value[11] * value[14] - 
		value[8]  * value[2] * value[15] + 
		value[8]  * value[3] * value[14] + 
		value[12] * value[2] * value[11] - 
		value[12] * value[3] * value[10];
	m[9] =	-value[0]  * value[9] * value[15] + 
		value[0]  * value[11] * value[13] + 
		value[8]  * value[1] * value[15] - 
		value[8]  * value[3] * value[13] - 
		value[12] * value[1] * value[11] + 
		value[12] * value[3] * value[9];
	m[13] =	value[0]  * value[9] * value[14] - 
		value[0]  * value[10] * value[13] - 
		value[8]  * value[1] * value[14] + 
		value[8]  * value[2] * value[13] + 
		value[12] * value[1] * value[10] - 
		value[12] * value[2] * value[9];
	m[2] =	value[1]  * value[6] * value[15] - 
		value[1]  * value[7] * value[14] - 
		value[5]  * value[2] * value[15] + 
		value[5]  * value[3] * value[14] + 
		value[13] * value[2] * value[7] - 
		value[13] * value[3] * value[6];
	m[6] =	-value[0]  * value[6] * value[15] + 
		value[0]  * value[7] * value[14] + 
		value[4]  * value[2] * value[15] - 
		value[4]  * value[3] * value[14] - 
		value[12] * value[2] * value[7] + 
		value[12] * value[3] * value[6];
	m[10] =	value[0]  * value[5] * value[15] - 
		value[0]  * value[7] * value[13] - 
		value[4]  * value[1] * value[15] + 
		value[4]  * value[3] * value[13] + 
		value[12] * value[1] * value[7] - 
		value[12] * value[3] * value[5];
	m[14] =	-value[0]  * value[5] * value[14] + 
		value[0]  * value[6] * value[13] + 
		value[4]  * value[1] * value[14] - 
		value[4]  * value[2] * value[13] - 
		value[12] * value[1] * value[6] + 
		value[12] * value[2] * value[5];
	m[3] =	-value[1] * value[6] * value[11] + 
		value[1] * value[7] * value[10] + 
		value[5] * value[2] * value[11] - 
		value[5] * value[3] * value[10] - 
		value[9] * value[2] * value[7] + 
		value[9] * value[3] * value[6];
	m[7] =	value[0] * value[6] * value[11] - 
		value[0] * value[7] * value[10] - 
		value[4] * value[2] * value[11] + 
		value[4] * value[3] * value[10] + 
		value[8] * value[2] * value[7] - 
		value[8] * value[3] * value[6];
	m[11] =	-value[0] * value[5] * value[11] + 
		value[0] * value[7] * value[9] + 
		value[4] * value[1] * value[11] - 
		value[4] * value[3] * value[9] - 
		value[8] * value[1] * value[7] + 
		value[8] * value[3] * value[5];
	m[15] =	value[0] * value[5] * value[10] - 
		value[0] * value[6] * value[9] - 
		value[4] * value[1] * value[10] + 
		value[4] * value[2] * value[9] + 
		value[8] * value[1] * value[6] - 
		value[8] * value[2] * value[5];
	return value[0]*m[0] + value[1]*m[4] + value[2]*m[8] + value[3]*m[12];
}

mat44 mat44::inverse() const {
	v16sd m;
	m[0] =	value[5] * value[10] * value[15] -
		value[5] * value[11] * value[14] -
		value[9] * value[6] * value[15] +
		value[9] * value[7] * value[14] +
		value[13] * value[6] * value[11] -
		value[13] * value[7] * value[10];
	m[4] =	-value[4]  * value[10] * value[15] + 
		value[4]  * value[11] * value[14] + 
		value[8]  * value[6]  * value[15] - 
		value[8]  * value[7]  * value[14] - 
		value[12] * value[6]  * value[11] + 
		value[12] * value[7]  * value[10];
	m[8] =	value[4]  * value[9] * value[15] - 
		value[4]  * value[11] * value[13] - 
		value[8]  * value[5] * value[15] + 
		value[8]  * value[7] * value[13] + 
		value[12] * value[5] * value[11] - 
		value[12] * value[7] * value[9];
	m[12] =	-value[4]  * value[9] * value[14] + 
		value[4]  * value[10] * value[13] +
		value[8]  * value[5] * value[14] - 
		value[8]  * value[6] * value[13] - 
		value[12] * value[5] * value[10] + 
		value[12] * value[6] * value[9];
	m[1] =	-value[1]  * value[10] * value[15] + 
		value[1]  * value[11] * value[14] + 
		value[9]  * value[2] * value[15] - 
		value[9]  * value[3] * value[14] - 
		value[13] * value[2] * value[11] + 
		value[13] * value[3] * value[10];
	m[5] =	value[0]  * value[10] * value[15] - 
		value[0]  * value[11] * value[14] - 
		value[8]  * value[2] * value[15] + 
		value[8]  * value[3] * value[14] + 
		value[12] * value[2] * value[11] - 
		value[12] * value[3] * value[10];
	m[9] =	-value[0]  * value[9] * value[15] + 
		value[0]  * value[11] * value[13] + 
		value[8]  * value[1] * value[15] - 
		value[8]  * value[3] * value[13] - 
		value[12] * value[1] * value[11] + 
		value[12] * value[3] * value[9];
	m[13] =	value[0]  * value[9] * value[14] - 
		value[0]  * value[10] * value[13] - 
		value[8]  * value[1] * value[14] + 
		value[8]  * value[2] * value[13] + 
		value[12] * value[1] * value[10] - 
		value[12] * value[2] * value[9];
	m[2] =	value[1]  * value[6] * value[15] - 
		value[1]  * value[7] * value[14] - 
		value[5]  * value[2] * value[15] + 
		value[5]  * value[3] * value[14] + 
		value[13] * value[2] * value[7] - 
		value[13] * value[3] * value[6];
	m[6] =	-value[0]  * value[6] * value[15] + 
		value[0]  * value[7] * value[14] + 
		value[4]  * value[2] * value[15] - 
		value[4]  * value[3] * value[14] - 
		value[12] * value[2] * value[7] + 
		value[12] * value[3] * value[6];
	m[10] =	value[0]  * value[5] * value[15] - 
		value[0]  * value[7] * value[13] - 
		value[4]  * value[1] * value[15] + 
		value[4]  * value[3] * value[13] + 
		value[12] * value[1] * value[7] - 
		value[12] * value[3] * value[5];
	m[14] =	-value[0]  * value[5] * value[14] + 
		value[0]  * value[6] * value[13] + 
		value[4]  * value[1] * value[14] - 
		value[4]  * value[2] * value[13] - 
		value[12] * value[1] * value[6] + 
		value[12] * value[2] * value[5];
	m[3] =	-value[1] * value[6] * value[11] + 
		value[1] * value[7] * value[10] + 
		value[5] * value[2] * value[11] - 
		value[5] * value[3] * value[10] - 
		value[9] * value[2] * value[7] + 
		value[9] * value[3] * value[6];
	m[7] =	value[0] * value[6] * value[11] - 
		value[0] * value[7] * value[10] - 
		value[4] * value[2] * value[11] + 
		value[4] * value[3] * value[10] + 
		value[8] * value[2] * value[7] - 
		value[8] * value[3] * value[6];
	m[11] =	-value[0] * value[5] * value[11] + 
		value[0] * value[7] * value[9] + 
		value[4] * value[1] * value[11] - 
		value[4] * value[3] * value[9] - 
		value[8] * value[1] * value[7] + 
		value[8] * value[3] * value[5];
	m[15] =	value[0] * value[5] * value[10] - 
		value[0] * value[6] * value[9] - 
		value[4] * value[1] * value[10] + 
		value[4] * value[2] * value[9] + 
		value[8] * value[1] * value[6] - 
		value[8] * value[2] * value[5];
	double det = value[0]*m[0] + value[1]*m[4] + value[2]*m[8] + value[3]*m[12];
	det = 1/det;
	v16sd out;
	for(int i=0;i<16;i++)
		out[i] = m[i]*det;
	return mat44(out);
}

vec3 operator*(const mat44& m2, const vec3& v2) {
	mat44& m = const_cast<mat44&>(m2);
	vec3& v = const_cast<vec3&>(v2);
	return vec3(v.x() * m[0] + v.y() * m[1] + v.z() * m[2] + m[3],
		v.x() * m[4] + v.y() * m[5] + v.z() * m[6] + m[7],
		v.x() * m[8] + v.y() * m[9] + v.z() * m[10] + m[11]);
}

vec3 operator*(const vec3& v2, const mat44& m2) {
	mat44& m = const_cast<mat44&>(m2);
	vec3& v = const_cast<vec3&>(v2);
	return vec3(v.x() * m[0] + v.y() * m[1] + v.z() * m[2] + m[3],
		v.x() * m[4] + v.y() * m[5] + v.z() * m[6] + m[7],
		v.x() * m[8] + v.y() * m[9] + v.z() * m[10] + m[11]);
}

vec3 operator*(double n, const vec3& v) {
	return v*n;
}

mat44 operator*(double n, const mat44& m) {
	return m*n;
}

