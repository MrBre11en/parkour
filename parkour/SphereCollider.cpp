#ifndef _SPHERECOLLIDER_C_
#define _SPHERECOLLIDER_C_

#include "component.h"

struct SphereCollider : Component
{
	float radius = 1.0f;
};

#endif