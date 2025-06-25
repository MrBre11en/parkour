#include "LevelManagerClass.h"

LevelManagerClass::LevelManagerClass()
{
	m_World = 0;
}

LevelManagerClass::LevelManagerClass(const LevelManagerClass& other)
{
}


LevelManagerClass::~LevelManagerClass()
{
}


void LevelManagerClass::Initialize()
{
	m_World = new World;

	Entity* cube = m_World->CreateEntity();
	Transform* transform = cube->AddComponent<Transform>();
	transform->position = vec3(0.0f, 5.0f, 0.0f);
	cube->AddComponent<PhysicBody>();
	cube->AddComponent<SphereCollider>();

	Entity* plane = m_World->CreateEntity();
	plane->AddComponent<Transform>();
	plane->AddComponent<PlaneCollider>();


	m_World->AddPhysicSystem<PhysicSystem>();
}


void LevelManagerClass::Shutdown()
{
	if (m_World)
	{
		delete m_World;
		m_World = 0;
	}
}


void LevelManagerClass::Frame()
{
	m_World->UpdatePhysic();
	m_World->UpdateRender();
}