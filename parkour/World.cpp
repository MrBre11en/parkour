////////////////////////////////////////////////////////////////////////////////
// Filename: World.cpp
////////////////////////////////////////////////////////////////////////////////
#include "World.h"


World::World()
{
}


Entity* World::CreateEntity()
{
	Entity* entity = new Entity;
	return entity;
}


void World::AddSystem(System& system)
{
	systems.push_back(system);
}


void World::Update()
{
	size_t size = systems.size();
	for (int i = 0; i < size; i++)
	{
		systems[i].Update(entities, 0.01f);
	}
}