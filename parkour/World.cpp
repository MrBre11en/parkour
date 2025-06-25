////////////////////////////////////////////////////////////////////////////////
// Filename: World.cpp
////////////////////////////////////////////////////////////////////////////////
#include "World.h"


World::World()
{
}


World::World(const World& other)
{
}


World::~World()
{
}


void World::Shutdown()
{
	size_t size = systems.size();
	for (int i = 0; i < size; i++)
	{
		systems[i]->Shutdown();
	}
}


Entity* World::CreateEntity()
{
	Entity* entity = new Entity;
	return entity;
}


void World::Update()
{
	size_t size = systems.size();
	for (int i = 0; i < size; i++)
	{
		systems[i]->Update(entities, 0.01f);
	}
}