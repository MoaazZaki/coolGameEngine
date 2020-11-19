#include "ComponentArray.hpp"

famm::ComponentArray::ComponentArray() {

	entriesCount = 0;

}

template<typename T>
void famm::ComponentArray::addData(Entity entity, T componentdata) {

	assert( entityIndexMap.find(entity) == entityIndexMap.end() && "Entity already has component data in the component array" );

	//insert componentdata at the end of the array
	componentArray[entriesCount] = componentdata;

	//link the entity and index in the maps
	entityIndexMap[entity] = entriesCount;
	indexEntityMap[entriesCount] = entity;

	//increment current entries count
	entriesCount++;

}

template<typename T>
void famm::ComponentArray::removeData(Entity entity) {

	assert(entityIndexMap.find(entity) != entityIndexMap.end() && "Entity already doesn't have component data in the component array");

	//index of the entity data to be removed
	size_t toBeRemovedComponentIndex = entityIndexMap[entity];

	//store the entity of the last entry in the array
	Entity lastComponentEntity = indexEntityMap[entriesCount - 1];

	//insert the last array entry at the index of the removed entry
	ComponentArray[toBeRemovedComponentIndex]= componentArray[entriesCount - 1];

	//update maps
	entityIndexMap[lastComponentEntity] = toBeRemovedComponentIndex;
	indexEntityMap[toBeRemovedComponentIndex] = lastComponentEntity;
	entityIndexMap.erase(entity);
	indexEntityMap.erase(entriesCount - 1);

	//decrement the number of current entries
	entriesCount--;

}

template<typename T>
T& famm::ComponentArray::getData(Entity entity) {

	assert(entityIndexMap.find(entity) != entityIndexMap.end() && "Entity already doesn't have component data in the component array");

	return componentArray[entityIndexMap[entity]];

}

void famm::ComponentArray::entityDestroyed(Entity entity) {

	//check if the entity has data in the current type of componentArray. If so, remove its data
	if (entityIndexMap.find(entity) != entityIndexMap.end()) removeData(entity);

}
