////////////////////////////////////////////////////////////////////////////////
// Filename: PhysicSystem.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PhysicSystem.h"

PhysicSystem::PhysicSystem()
{
}


void PhysicSystem::Update(vector<Entity>& entities, float deltaTime)
{
	size_t size = entities.size();
	for (int i = 0; i < size; i++)
	{
		Entity entity = entities[i];
		PhysicBody* physicBody = entity.GetComponent<PhysicBody>();
		Transform* transform = entity.GetComponent<Transform>();
		if (physicBody != nullptr && transform != nullptr)
		{

			if (physicBody->useGravity)
			{

			}

			transform->position += physicBody->velocity * deltaTime;
		}
	}
}