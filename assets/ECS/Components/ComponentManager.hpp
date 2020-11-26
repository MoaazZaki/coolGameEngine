#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.hpp"
#include <data-types.h>
#include <unordered_map>

namespace famm {

	class ComponentManager
	{

	private:

		std::unordered_map<const char*, ComponentType> componentTypes;				//map storing the name and id of each component type
		std::unordered_map<const char*, ComponentArrayInterface*> componentArrays;	//map storing the name of every component type and a pointer to its componentarray
		ComponentType componentTypesCount;											//for assigning ids for newly created component types

		//helper function to return a pointer to the componentarray of a certain component type
		template<typename T>
		ComponentArray<T>* getComponentArray() {

			//get the component type name
			const char* componentTypeName = typeid(T).name();
			assert(componentTypes.find(componentTypeName) != componentTypes.end() && "Component type doesn't currently exist.");

			//get a pointer to the componentArray of the desired component type
			return (ComponentArray<T>*) componentArrays[componentTypeName];

		}									

	public:

		//constructor initializes componentTypesCount with 0
		ComponentManager() {
			componentTypesCount = 0;
		}										

		//add a new component type (name and id) to the componentTypes map
		template<typename T>
		void addComponentType() {

			//get the component type name
			const char* componentTypeName = typeid(T).name();
			assert(componentTypes.find(componentTypeName) == componentTypes.end() && "Component type already defined.");

			//add the component type name and id tp the componentTypes map 
			componentTypes.insert({ componentTypeName, componentTypesCount });

			//increment the component types count to be assigned as the id value of the next defined component type
			componentTypesCount++;

		}								

		//get the componentType (id) of a certain component type (T= component type name)
		template<typename T>
		ComponentType getComponentType() {

			//get the component type name
			const char* componentTypeName = typeid(T).name();

			assert(componentTypes.find(componentTypeName) != componentTypes.end() && "Component type doesn't currently exist.");

			return componentTypes[componentTypeName];

		}						

		//add entity component data for a specific component type in the right componentArray
		template<typename T>
		void addComponentData(Entity entity, T componentdata) {

			ComponentArray<T>* cArrPtr = getComponentArray<T>();
			cArrPtr->addData(entity, componentdata);

		}	

		//remove entity component data for a specific component type from the right componentArray
		template<typename T>
		void removeComponentData(Entity entity) {

			ComponentArray<T>* cArrPtr = getComponentArray<T>();
			cArrPtr->removeData(entity);

		}				

		//get the component data of a specific component type for a given entity from the right componenetArray
		template<typename T>
		T& getComponentData(Entity entity) {

			ComponentArray<T>* cArrPtr = getComponentArray<T>();
			return cArrPtr->getData(entity);

		}						

		//notify all componentArrays that the entity is destroyed to remove its records if they exist
		void entityDestroyed(Entity entity) {

			//iterate over componentArrays map and call entityDestroyed for all to delete the entity records from corresponding componentArrays
			for (auto& it : componentArrays) it.second->entityDestroyed(entity);

		}	

	};


}
#endif