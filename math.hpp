#pragma once

// Vector type definitions
typedef double v2sd __attribute__((vector_size(16)));
typedef double v4sd __attribute__((vector_size(32)));
typedef double v16sd __attribute__((vector_size(128)));

class vec2 {
	v2sd value;

	vec2(v2sd v);
public:
	vec2();
	vec2(double x, double y);

	double& x();
	double& y();
	double gx() const;
	double gy() const;

	vec2 operator+(const vec2& v) const;
	vec2 operator-() const;
	vec2 operator-(const vec2& v) const;
	vec2 operator*(double n) const;
	vec2 operator/(double n) const;

	vec2& operator+=(const vec2& v);
	vec2& operator-=(const vec2& v);
	vec2& operator*=(double n);
	vec2& operator/=(double n);

	bool operator==(const vec2& v) const;
	bool operator!=(const vec2& v) const;

	double lengthSquared() const;
	double length() const;
	vec2& normalize();
	vec2 normalized() const;

	double dot(const vec2& other) const;
};

class vec3 {
	v4sd value;

	vec3(v4sd v);
public:
	vec3();
	vec3(double x, double y, double z);

	double& x();
	double& y();
	double& z();
	double gx() const;
	double gy() const;
	double gz() const;

	vec3 operator+(const vec3& v) const;
	vec3 operator-() const;
	vec3 operator-(const vec3& v) const;
	vec3 operator*(double n) const;
	vec3 operator/(double n) const;

	vec3& operator+=(const vec3& v);
	vec3& operator-=(const vec3& v);
	vec3& operator*=(double n);
	vec3& operator/=(double n);

	bool operator==(const vec3& v) const;
	bool operator!=(const vec3& v) const;

	double lengthSquared() const;
	double length() const;
	vec3& normalize();
	vec3 normalized() const;

	vec3 cross(const vec3& other) const;
	double dot(const vec3& other) const;
};

class mat22 {
	v4sd value;

	mat22(v4sd v);
public:
	mat22(); // Identity matrix
	mat22(double a[]); // Direct
	mat22(double ang); // Rotation

	double& a();
	double& b();
	double& c();
	double& d();

	mat22 operator+(const mat22& m) const;
	mat22 operator-(const mat22& m) const;
	mat22 operator*(const mat22& m) const;
	mat22 operator*(double n) const;

	double det() const;
	mat22 inverse() const;
};

class mat44 {
	v16sd value;
	
	mat44(v16sd value);
public:
	mat44();
	mat44(double v[]);

	double& operator[](int n);

	mat44 operator+(const mat44& m) const;
	mat44 operator-(const mat44& m) const;
	mat44 operator*(const mat44& m) const;
	mat44 operator*(double n) const;

	double det() const;
	mat44 inverse() const;

	static mat44 translate(vec3 v);
	static mat44 rotate(vec3 axis, double angle);
};

vec3 operator*(const mat44& m, const vec3& v);
vec3 operator*(const vec3& v, const mat44& m);
vec3 operator*(double n, const vec3& v);
mat44 operator*(double n, const mat44& m);

#define PI 3.14159265358979
