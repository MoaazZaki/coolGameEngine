//#include "ECSManager.hpp"
//
//famm::ECSManager::ECSManager() {
//
//	eManagerPtr = new EntityManager;
//	cManagerPtr = new ComponentManager;
//	sManagerPtr = new SystemManager;
//
//}
//
////------------------------Entity Functions-----------------------------//
//
//famm::Entity famm::ECSManager::createEntity() {
//
//	return eManagerPtr->createEntity();
//
//}
//
//void famm::ECSManager::destroyEntity(Entity entity) {
//
//	eManagerPtr->destroyEntity(entity);
//	cManagerPtr->entityDestroyed(entity);
//	sManagerPtr->entityDestroyed(entity);
//
//}
//
////------------------------Component Functions-----------------------------//
//
//template<typename T>
//void famm::ECSManager::addComponentType() {
//
//	cManagerPtr->addComponentType<T>();
//
//}
//
//template<typename T>
//famm::ComponentType famm::ECSManager::getComponentType() {
//
//	return cManagerPtr->getComponentType<T>();
//
//}
//
//template<typename T>
//void famm::ECSManager::addComponentData(Entity entity, T componentdata) {
//
//	//add the component data to the entity
//	cManagerPtr->addComponentData<T>(entity, componentdata);
//
//	//update the entity signature 
//	Signature eSignature = eManagerPtr->getSignature(entity);
//	eSignature.set(cManagerPtr->getComponentType<T>(), true);
//	eManagerPtr->setSignature(entity, eSignature);
//
//	//inform systems of the change in entity signature
//	sManagerPtr->entitySignatureChanged(entity, eSignature);
//}
//
//template<typename T>
//void famm::ECSManager::removeComponentData(Entity entity) {
//
//	//remove the component data from the entity
//	cManagerPtr->removeComponentData<T>(entity);
//
//	//update the entity signature 
//	Signature eSignature = eManagerPtr->getSignature(entity);
//	eSignature.set(cManagerPtr->getComponentType<T>(), false);
//	eManagerPtr->setSignature(entity, eSignature);
//
//	//inform systems of the change in entity signature
//	sManagerPtr->entitySignatureChanged(entity, eSignature);
//
//}
//
//template<typename T>
//T& famm::ECSManager::getComponentData(Entity entity) {
//
//	return cManagerPtr->getComponentData<T>(entity);
//
//}
//
////------------------------System Functions-----------------------------//
//template<typename T>
//T* famm::ECSManager::addSystem() {
//
//	return sManagerPtr->addSystem<T>();
//}
//
//template<typename T>
//void famm::ECSManager::setSystemSignature(Signature signature) {
//
//	sManagerPtr->setSignature<T>(signature);
//
//}