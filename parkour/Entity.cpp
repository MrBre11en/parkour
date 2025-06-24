////////////////////////////////////////////////////////////////////////////////
// Filename: Entity.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Entity.h"

Entity::Entity()
{
}


template <typename T>
void Entity::AddComponent(T* component)
{
	components[typeid(T)] = component;
}


template <typename T>
void Entity::RemoveComponent()
{
	Component* component = GetComponent<T>();
	if (component != nullptr)
	{
		delete component;
	}
	components.erase(typeid(T));
}


template <typename T>
T* Entity::GetComponent()
{
	auto it = components.find(typeid(T));
	return (it != components.end()) ? static_cast<T*>(it->second) : nullptr;
}


template <typename T>
bool Entity::HasComponent()
{
	Component* component = GetComponent<T>();
	if (component != nullptr)
	{
		return true;
	}
	return false;
}