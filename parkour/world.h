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

////////////////////////////////////////////////////////////////////////////////
// Class name: World
////////////////////////////////////////////////////////////////////////////////
class World
{
public:
	World();
	World(const World&);
	~World();

	template <typename T>
	T* AddSystem()
	{
		auto system = make_unique<T>();
		T* raw_ptr = system.get();
		system->Initialize();
		systems.push_back(move(system));

		return raw_ptr;
	}

	Entity* CreateEntity();

	void Shutdown();
	void Update();
private:
	vector<Entity> entities;
	vector<unique_ptr<System>> systems;
};

#endif