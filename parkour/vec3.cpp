#ifndef _VEC3_STRUCT_
#define _VEC3_STRUCT_

#include <cmath>
#include <iostream>

struct vec3
{
	float x, y, z;

	vec3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
		: x(X), y(Y), z(Z)
	{}


	float magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	float dot(const vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}


	vec3 operator+(const vec3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	inline vec3 operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3 operator-(const vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	inline vec3 operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3 operator*(float num) const {
		return { x * num, y * num, z * num };
	}

	vec3 operator*(const vec3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	inline vec3 operator*=(float num) {
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	inline vec3 operator*=(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3 operator/(float num) const {
		return { x / num, y / num, z / num };
	}

	vec3 operator/(const vec3& other) const {
		return { x / other.x, y / other.y, z / other.z };
	}

	inline vec3 operator/=(float num) {
		x /= num;
		y /= num;
		z /= num;
		return *this;
	}

	inline vec3 operator/=(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}


	friend std::ostream& operator<<(std::ostream& os, const vec3& v) {
		return os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
};

#endif