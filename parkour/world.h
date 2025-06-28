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

	template<typename... TComponents>
	vector<tuple<Entity*, TComponents&...>> GetEntitiesWith() {
		constexpr auto key = GetComponentSetKey<TComponents...>();

		if (componentToEntities.contains(key)) {
			return GetCachedEntities<TComponents...>(key);
		}

		// Первый раз - фильтруем и кешируем
		vector<tuple<Entity*, TComponents&...>> result;
		for (auto& entity : entities) {
			if ((entity.template HasComponent<TComponents>() && ...)) {
				result.emplace_back(
					&entity,
					entity.template GetComponent<TComponents>()...
				);
			}
		}
		componentToEntities[key] = result | views::transform([](auto& tuple) {
			return get<0>(tuple);
		}) | ranges::to<vector>();

		return result;
	}

	Entity* CreateEntity();

	bool Initialize(D3DClass*, BitmapClass*, ShaderManagerClass*);
	void Shutdown();
	bool UpdatePhysic();
	bool UpdateRender();

private:
	template<typename... TComponents>
	constexpr size_t GetComponentSetKey() {
		array<size_t, sizeof...(TComponents)> types = { typeid(TComponents).hash_code()... };
		sort(types.begin(), types.end());
		size_t key = 0;
		for (auto t : types) {
			key ^= t + 0x9e3779b9 + (key << 6) + (key >> 2);
		}
		return key;
	}

	template<typename... TComponents>
	auto GetCachedEntities(std::size_t key) {
		std::vector<std::tuple<Entity*, TComponents&...>> result;
		for (Entity* entity : componentToEntities[key]) {
			result.emplace_back(
				entity,
				entity->template GetComponent<TComponents>()...
			);
		}
		return result;
	}

private:
	vector<Entity*> entities;
	unordered_map<size_t, vector<Entity*>> componentToEntities;
	vector<unique_ptr<System>> physicSystems;
	vector<unique_ptr<System>> renderSystems;
};

#endif