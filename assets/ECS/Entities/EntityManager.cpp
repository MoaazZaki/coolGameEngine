#include "EntityManager.hpp"

famm::EntityManager::EntityManager() {
	
	for (auto e = 0; e < MAX_ENTITIES; e++) remainingEntities.push(e);
	for (auto s = 0; s < MAX_ENTITIES; s++) entitySignatures[s] = 0;
	aliveEntitiesCount = 0;

}

famm::Entity famm::EntityManager::createEntity() {

	assert(remainingEntities.size() != 0 && "Maximum alive entities count exceeded");

	Entity Id= remainingEntities.front();
	remainingEntities.pop();
	aliveEntitiesCount++; 
	return Id;
	
}

void famm::EntityManager::destroyEntity(Entity entity) {

	assert(entity < MAX_ENTITIES && "Entity doesn't exist");

	entitySignatures[entity] = 0;
	aliveEntitiesCount--;
	remainingEntities.push(entity);
}

void famm::EntityManager::setSignature(Entity entity, Signature signature) {

	assert(entity < MAX_ENTITIES && "Entity doesn't exist");

	entitySignatures[entity] = signature;
}

famm::Signature famm::EntityManager::getSignature(Entity entity) {

	assert(entity < MAX_ENTITIES && "Entity doesn't exist");

	return entitySignatures[entity];
}