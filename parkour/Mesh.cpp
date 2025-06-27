#ifndef _MESH_C_
#define _MESH_C_

#include "component.h"
#include "modelclass.h"

struct Mesh : Component
{
	ModelClass model = ModelClass();
};

#endif