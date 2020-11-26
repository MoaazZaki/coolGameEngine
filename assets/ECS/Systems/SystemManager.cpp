//#include "SystemManager.hpp"
//
//template<typename T>
//T* famm::SystemManager::addSystem() {
//	
//	//get the system name
//	const char* systemName = typeid(T).name();
//	assert(systems.find(componentTypeName) == system.end() && "System already defined.");
//
//	//create a pointer to the system, add the system name and pointer to the systems map, and return the system pointer
//	T* sPtr;
//	systems.insert({ systemName,sPtr });
//	return sPtr;
//
//}
//
//template<typename T>
//void famm::SystemManager::setSignature(Signature signature) {
//
//	//get the system name
//	const char* systemName = typeid(T).name();
//	assert(systems.find(componentTypeName) != system.end() && "System doesn't exist.");
//
//	//insert system name and signature in the systemSignatures map
//	systemSignatures.insert({ systemName,signature });
//
//}
//
//void famm::SystemManager::entityDestroyed(Entity entity) {
//
//	//iterate over the entitiesSet of all systems and erase the destroyed entity if exists
//	for (auto& it : systems) it.second-> entitiesSet.erase(entity);
//
//}
//
//void famm::SystemManager::entitySignatureChanged(Entity entity, Signature newEntitySignature) {
//
//	//iterate over the entitiesSet of all systems 
//	for (auto& it : systems) {
//
//		//if the entity signature matches the system signature (has all components in system signature), add it to the system's entitiesSet
//		if ((newEntitySignature & systemSignatures[it.first]) == systemSignatures[it.first]) it.second->entitiesSet.insert(entity);
//
//		//if the entity's new signature mismatches the system's, remove it from the entitiesSet
//		else it.second->entitiesSet.erase(entity);
//
//		
//	}
//
//}