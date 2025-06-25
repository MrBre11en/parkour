#ifndef _PLANECOLLIDER_C_
#define _PLANECOLLIDER_C_

#include "component.h"
#include "vec3.cpp"

struct PlaneCollider : Component
{
	vec3 normal = vec3();
};

#endif