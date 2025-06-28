////////////////////////////////////////////////////////////////////////////////
// Filename: world.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WORLD_H_
#define _WORLD_H_

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <memory>
#include "component.h"
#include "entity.h"
#include "system.h"

#include "d3dclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "pointlightclass.h"
#include "bitmapclass.h"
#include "shadermanagerclass.h"

using namespace std;

/////////////
// GLOBALS //
/////////////
const float PHYSICS_DT = 1.0f / 60.0f; // 60 FPS
const float RENDER_DT = 1.0f / 144.0f; // 144 FPS


////////////////////////////////////////////////////////////////////////////////
// Class name: World
////////////////////////////////////////////////////////////////////////////////
class World
{
public:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	LightClass* m_Light;
	PointLightClass* m_PointLights;
	int m_numPointLights;
	BitmapClass* m_Bitmap;
	ShaderManagerClass* m_ShaderManager;

public:
	World();
	World(const World&);
	~World();

	template <typename T, typename... Args>
	T* AddPhysicSystem(Args&&... args)
	{
		auto system = make_unique<T>(forward<Args>(args)...);
		T* raw_ptr = system.get();
		system->Initialize();
		physicSystems.push_back(move(system));

		return raw_ptr;
	}

	template <typename T, typename... Args>
	T* AddRenderSystem(Args&&... args)
	{
		auto system = make_unique<T>(forward<Args>(args)...);
		T* raw_ptr = system.get();
		system->Initialize();
		renderSystems.push_back(move(system));

		return raw_ptr;
	}

	Entity* CreateEntity();

	bool Initialize(D3DClass*, BitmapClass*, ShaderManagerClass*);
	void Shutdown();
	bool UpdatePhysic();
	bool UpdateRender();

private:
	vector<Entity*> entities;
	vector<unique_ptr<System>> physicSystems;
	vector<unique_ptr<System>> renderSystems;
};

#endif