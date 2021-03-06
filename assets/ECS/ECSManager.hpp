#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "Entities/EntityManager.hpp"
#include "Components/ComponentManager.hpp"
#include "Systems/SystemManager.hpp"

namespace famm {

	class ECSManager
	{
	private:

		std::unique_ptr<EntityManager> eManagerPtr;				//entity manager pointer
		std::unique_ptr<ComponentManager> cManagerPtr;			//component manager pointer
		std::unique_ptr<SystemManager> sManagerPtr;				//system manager pointer

	public:

		//constructor to initialize manager pointers
		ECSManager() {

			eManagerPtr = std::make_unique<EntityManager>();
			cManagerPtr = std::make_unique<ComponentManager>() ;
			sManagerPtr = std::make_unique<SystemManager>() ;

		}

		//-------------------------Entity Functions------------------------//
		Entity createEntity() {

			return eManagerPtr->createEntity();

		}

		void destroyEntity(Entity entity) {

			eManagerPtr->destroyEntity(entity);
			cManagerPtr->entityDestroyed(entity);
			sManagerPtr->entityDestroyed(entity);

		}

		//-------------------------Component Functions------------------------//
		template<typename T>
		void addComponentType() {

			cManagerPtr->addComponentType<T>();

		}

		template<typename T>
		ComponentType getComponentType() {

			return cManagerPtr->getComponentType<T>();

		}

		template<typename T>
		void addComponentData(Entity entity, T componentdata) {

			//add the component data to the entity
			cManagerPtr->addComponentData<T>(entity, componentdata);

			//update the entity signature 
			Signature eSignature = eManagerPtr->getSignature(entity);
			eSignature.set(cManagerPtr->getComponentType<T>(), true);
			eManagerPtr->setSignature(entity, eSignature);

			//inform systems of the change in entity signature
			sManagerPtr->entitySignatureChanged(entity, eSignature);
		}

		template<typename T>
		void removeComponentData(Entity entity) {

			//remove the component data from the entity
			cManagerPtr->removeComponentData<T>(entity);

			//update the entity signature 
			Signature eSignature = eManagerPtr->getSignature(entity);
			eSignature.set(cManagerPtr->getComponentType<T>(), false);
			eManagerPtr->setSignature(entity, eSignature);

			//inform systems of the change in entity signature
			sManagerPtr->entitySignatureChanged(entity, eSignature);

		}

		template<typename T>
		T& getComponentData(Entity entity) {

			return cManagerPtr->getComponentData<T>(entity);

		}

		//-------------------------System Functions------------------------//
		template<typename T>
		std::shared_ptr<T> addSystem() {

			return sManagerPtr->addSystem<T>();
		}

		template<typename T>
		void setSystemSignature(Signature signature) {

			sManagerPtr->setSignature<T>(signature);

		}
	};

}
#endif