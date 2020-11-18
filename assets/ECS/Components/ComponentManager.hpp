#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <ComponentArray.hpp>
#include <data-types.h>
#include <unordered_map>

namespace famm {

	class ComponentManager
	{
	private:

		std::unordered_map<const char*, ComponentType> componentTypes;				//map storing the name and id of each component type
		std::unordered_map<const char*, ComponentArrayInterface*> componentArrays;	//map storing the name of every component type and a pointer to its componentarray
		ComponentType componentTypesCount;											//for assigning ids for newly created component types

		template<typename T>
		ComponentArray<T>* getComponentArray();										//helper function to return a pointer to the componentarray of a certain component type

	public:
		ComponentManager();										//constructor initializes componentTypesCount with 0

		template<typename T>
		void addComponentType();								//add a new component type (name and id) to the componentTypes map

		template<typename T>
		ComponentType getComponentType();						//get the componentType (id) of a certain component type (T= component type name)

		template<typename T>
		void addComponentData(Entity entity, T componentdata);	//add entity component data for a specific component type in the right componentArray

		template<typename T>
		void removeComponentData(Entity entity);				//remove entity component data for a specific component type from the right componentArray

		template<typename T>
		T& getComponentData(Entity entity);						//get the component data of a specific component type for a given entity from the right componenetArray

		void entityDestroyed(Entity entity);					//notify all componentArrays that the entity is destroyed to remove its records if they exist
	};

}
#endif