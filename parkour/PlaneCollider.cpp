#ifndef _PLANECOLLIDER_C_
#define _PLANECOLLIDER_C_

#include "component.h"
#include "vec3.cpp"

struct PlaneCollider : Component
{
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);
};

#endif