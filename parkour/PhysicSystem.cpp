#ifndef _PHYSIC_SYSTEM_
#define _PHYSIC_SYSTEM_

//////////////
// INCLUDES //
//////////////
#include<cmath>
#include "system.h"
#include "Transform.cpp"
#include "PhysicBody.cpp"

/////////////
// GLOBALS //
/////////////
const float GravityAcceleration = 9.8f;


class PhysicSystem: public System
{
public:
	PhysicSystem()
	{
		gravityVector = 0;
	}



	bool Initialize() override
	{
		gravityVector = new vec3(0.0f, -GravityAcceleration, 0.0f);
		return true;
	}


	void Shutdown() override
	{
		if (gravityVector)
		{
			delete gravityVector;
			gravityVector = 0;
		}
	}


	bool Update(vector<Entity*>& entities, float deltaTime) override
	{
		size_t size = entities.size();
		for (int i = 0; i < size; i++)
		{
			Entity* entity = entities[i];
			Transform* transform = entity->GetComponent<Transform>();
			PhysicBody* physicBody = entity->GetComponent<PhysicBody>();
			if (transform != nullptr && physicBody != nullptr)
			{
				if (physicBody->useGravity)
				{
					physicBody->velocity += *gravityVector * deltaTime;
				}

				transform->position += physicBody->velocity * deltaTime;
			}
		}

		return true;
	}

private:
	vec3* gravityVector;
};

#endif