#include "ComponentManager.hpp"

template<typename T>
famm::ComponentArray<T>* famm::ComponentManager::getComponentArray() {

	//get the component type name
	const char* componentTypeName = typeid(T).name();
	assert(componentTypes.find(componentTypeName) != componentTypes.end() && "Component type doesn't currently exist.");

	//get a pointer to the componentArray of the desired component type
	return (ComponentArray<T>*) componentArrays[componentTypeName];

}


famm::ComponentManager::ComponentManager() {

	componentTypesCount = 0;

}

template<typename T>
void famm::ComponentManager::addComponentType() {

	//get the component type name
	const char* componentTypeName = typeid(T).name();
	assert(componentTypes.find(componentTypeName) == componentTypes.end() && "Component type already defined." );

	//add the component type name and id tp the componentTypes map 
	componentTypes.insert({ componentTypeName, componentTypesCount });

	//increment the component types count to be assigned as the id value of the next defined component type
	componentTypesCount++;

}

template<typename T>
famm::ComponentType famm::ComponentManager::getComponentType() {

	//get the component type name
	const char* componentTypeName = typeid(T).name();

	assert(componentTypes.find(componentTypeName) != componentTypes.end() && "Component type doesn't currently exist.");

	return componentTypes[componentTypeName];

}

template<typename T>
void famm::ComponentManager::addComponentData(Entity entity, T componentdata) {

	ComponentArray<T>* cArrPtr = getComponentArray<T>();
	cArrPtr->addData(entity, componentdata);

}

template<typename T>
void famm::ComponentManager::removeComponentData(Entity entity) {

	ComponentArray<T>* cArrPtr = getComponentArray<T>();
	cArrPtr->removeData(entity);

}

template<typename T>
T& famm::ComponentManager::getComponentData(Entity entity) {

	ComponentArray<T>* cArrPtr = getComponentArray<T>();
	return cArrPtr->getData(entity);

}

void famm::ComponentManager::entityDestroyed(Entity entity) {

	//iterate over componentArrays map and call entityDestroyed for all to delete the entity records from corresponding componentArrays
	for (auto& it : componentArrays) it.second->entityDestroyed(entity);

}