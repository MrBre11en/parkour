#include <cmath>

struct vec3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	vec3(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{}


	float magnitude() {
		return sqrt(x * x + y * y + z * z);
	}


	vec3 operator+(const vec3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	vec3 operator-(const vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	vec3 operator*(float num) const {
		return { x * num, y * num, z * num };
	}

	vec3 operator*(const vec3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	vec3 operator/(float num) const {
		return { x / num, y / num, z / num };
	}

	vec3 operator/(const vec3& other) const {
		return { x / other.x, y / other.y, z / other.z };
	}
};