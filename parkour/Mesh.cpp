#ifndef _MESH_C_
#define _MESH_C_

#include "component.h"
#include "vec3.cpp"

struct Mesh : Component
{
	float mass = 1.0f;
	vec3 velocity = vec3();
	bool useGravity = true;
};

#endif