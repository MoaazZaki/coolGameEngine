#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <data-types.h>
namespace famm {

	class ComponentManager
	{
	private:


	public:
		ComponentManager() {}

		template<typename T>
		void RegisterComponent() {}

		template<typename T>
		componentType GetComponentType() {}

		template<typename T>
		void AddComponent(Entity entity, T component){}

		template<typename T>
		void RemoveComponent(Entity entity) {}

		template<typename T>
		T& GetComponent(Entity entity){}

		void EntityDestroyed(Entity entity){}
	};

}
#endif