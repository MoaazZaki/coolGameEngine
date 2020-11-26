#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "ComponentArrayInterface.hpp"
#include <unordered_map>
#include <data-types.h>

namespace famm {

	template<typename T>
	class ComponentArray : public ComponentArrayInterface {

	private:

		std::array<T, MAX_ENTITIES> componentArray;			//array of size MAX_ENTITIES holding the current component values for relevant entities
		std::unordered_map<Entity, size_t> entityIndexMap;	//mapping current entity ids to the componentarray indices 
		std::unordered_map<size_t, Entity> indexEntityMap;	//mapping componentarray indices to current entity ids
		size_t entriesCount;								//number of valid entries in the componentarray

	public:

		ComponentArray() {

			entriesCount = 0;

		}									//constructor: set entriesCount to 0

		void addData(Entity entity, T componentdata) {

			assert(entityIndexMap.find(entity) == entityIndexMap.end() && "Entity already has component data in the component array");

			//insert componentdata at the end of the array
			componentArray[entriesCount] = componentdata;

			//link the entity and index in the maps
			entityIndexMap[entity] = entriesCount;
			indexEntityMap[entriesCount] = entity;

			//increment current entries count
			entriesCount++;

		}		//insert component data of entity in the componentarray

		void removeData(Entity entity) {

			assert(entityIndexMap.find(entity) != entityIndexMap.end() && "Entity already doesn't have component data in the component array");

			//index of the entity data to be removed
			size_t toBeRemovedComponentIndex = entityIndexMap[entity];

			//store the entity of the last entry in the array
			Entity lastComponentEntity = indexEntityMap[entriesCount - 1];

			//insert the last array entry at the index of the removed entry
			componentArray[toBeRemovedComponentIndex] = componentArray[entriesCount - 1];

			//update maps
			entityIndexMap[lastComponentEntity] = toBeRemovedComponentIndex;
			indexEntityMap[toBeRemovedComponentIndex] = lastComponentEntity;
			entityIndexMap.erase(entity);
			indexEntityMap.erase(entriesCount - 1);

			//decrement the number of current entries
			entriesCount--;

		}						//remove component data of entity from the componentarray

		T& getData(Entity entity) {

			assert(entityIndexMap.find(entity) != entityIndexMap.end() && "Entity already doesn't have component data in the component array");

			return componentArray[entityIndexMap[entity]];

		}							//get the component data of a specific entity

		void entityDestroyed(Entity entity) override {

			//check if the entity has data in the current type of componentArray. If so, remove its data
			if (entityIndexMap.find(entity) != entityIndexMap.end()) removeData(entity);

		}		//remove destroyed entity data from the componentarray

	};


}
#endif