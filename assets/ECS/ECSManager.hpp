#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "Entities/EntityManager.hpp"
#include "Components/ComponentManager.hpp"
#include "Systems/SystemManager.hpp"

namespace famm {

	class ECSManager
	{
	private:

		EntityManager* eManagerPtr;				//entity manager pointer
		ComponentManager* cManagerPtr;			//component manager pointer
		SystemManager* sManagerPtr;				//system manager pointer

	public:

		ECSManager();							//constructor to initialize manager pointers

		//EntityManager Functions
		Entity createEntity();

		void destroyEntity(Entity entity);

		//ComponentManager Functions
		template<typename T>
		void addComponentType();						

		template<typename T>
		ComponentType getComponentType();					

		template<typename T>
		void addComponentData(Entity entity, T componentdata);	

		template<typename T>
		void removeComponentData(Entity entity);				

		template<typename T>
		T& getComponentData(Entity entity);

		//SystemManager Functions
		template<typename T>
		T* addSystem();								

		template<typename T>
		void setSystemSignature(Signature signature);
	};

}
#endif