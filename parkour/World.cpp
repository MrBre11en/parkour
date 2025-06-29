////////////////////////////////////////////////////////////////////////////////
// Filename: World.cpp
////////////////////////////////////////////////////////////////////////////////
#include "World.h"


World::World()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Light = 0;
	m_PointLights = 0;
	m_Bitmap = 0;
	m_ShaderManager = 0;
}


World::World(const World& other)
{
}


World::~World()
{
}


bool World::Initialize(D3DClass* direct3D, BitmapClass* bitmap, ShaderManagerClass* shadermanager)
{
	m_Direct3D = direct3D;
	m_Bitmap = bitmap;
	m_ShaderManager = shadermanager;


	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 3.0f, -12.0f);
	m_Camera->SetRotation(15.0f, 0.0f, 0.0f);


	m_Light = new LightClass;

	m_Light->SetDirection(1.0f, -1.0f, 0.5f);
	m_Light->SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light->SetDiffuseColor(0.25f, 0.25f, 0.25f, 1.0f);
	m_Light->SetSpecularColor(0.25f, 0.25f, 0.25f, 1.0f);
	m_Light->SetSpecularPower(32.0f);


	m_numPointLights = 4;
	m_PointLights = new PointLightClass[m_numPointLights];

	m_PointLights[0].SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red
	m_PointLights[0].SetPosition(-3.0f, 1.0f, 3.0f);

	m_PointLights[1].SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green
	m_PointLights[1].SetPosition(3.0f, 1.0f, 0.0f);

	m_PointLights[2].SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue
	m_PointLights[2].SetPosition(-3.0f, 1.0f, -3.0f);

	m_PointLights[3].SetDiffuseColor(1.0f, 0.0f, 1.0f, 1.0f);  // Purpe
	m_PointLights[3].SetPosition(0.0f, 3.0f, 0.0f);


	return true;
}


void World::Shutdown()
{
	size_t size = physicSystems.size();
	for (int i = 0; i < size; i++)
	{
		physicSystems[i]->Shutdown();
	}

	size = renderSystems.size();
	for (int i = 0; i < size; i++)
	{
		renderSystems[i]->Shutdown();
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_PointLights)
	{
		delete[] m_PointLights;
		m_PointLights = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Bitmap)
	{
		m_Bitmap = 0;
	}

	if (m_ShaderManager)
	{
		m_ShaderManager = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D = 0;
	}
}


Entity* World::CreateEntity()
{
	Entity* entity = new Entity;
	entities.push_back(entity);

	return entity;
}


bool World::UpdatePhysic()
{
	bool result;
	size_t size = physicSystems.size();
	for (int i = 0; i < size; i++)
	{
		result = physicSystems[i]->Update(entities, 0.01f);
		if (!result)
		{
			return false;
		}
	}
}


bool World::UpdateRender()
{
	bool result;
	size_t size = renderSystems.size();
	for (int i = 0; i < size; i++)
	{
		result = renderSystems[i]->Update(entities, 0.01f);
		if (!result)
		{
			return false;
		}
	}
}