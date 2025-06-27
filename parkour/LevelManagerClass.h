﻿////////////////////////////////////////////////////////////////////////////////
// Filename: LevelManagerClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LEVELMANAGERCLASS_H_
#define _LEVELMANAGERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "pointlightclass.h"
#include "bitmapclass.h"
#include "shadermanagerclass.h"

#include "world.h"
#include "system.h"
#include "entity.h"
#include "component.h"

#include "Transform.cpp"
#include "PhysicBody.cpp"
#include "SphereCollider.cpp"
#include "PlaneCollider.cpp"
#include "Mesh.cpp"

#include "PhysicSystem.cpp"
#include "MeshRenderSystem.cpp"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;


////////////////////////////////////////////////////////////////////////////////
// Class name: LevelManagerClass
////////////////////////////////////////////////////////////////////////////////

class LevelManagerClass
{
public:
	LevelManagerClass();
	LevelManagerClass(const LevelManagerClass&);
	~LevelManagerClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float);

private:
	World* m_World;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	LightClass* m_Light;
	PointLightClass* m_PointLights;
	int m_numPointLights;
	BitmapClass* m_Bitmap;
	ShaderManagerClass* m_ShaderManager;
};

#endif