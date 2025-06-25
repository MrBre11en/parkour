#ifndef _PHYSICBODY_C_
#define _PHYSICBODY_C_

#include "component.h"
#include "vec3.cpp"

struct PhysicBody : Component
{
	float mass = 1.0f;
	vec3 velocity = vec3();
	bool useGravity = true;
};

#endif