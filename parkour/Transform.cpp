#ifndef _TRANSFORM_C_
#define _TRANSFORM_C_

#include "component.h"
#include "vec3.cpp"


struct Transform : Component
{
	vec3 position = vec3();
	vec3 rotation = vec3();
	vec3 scale = vec3();
};

#endif