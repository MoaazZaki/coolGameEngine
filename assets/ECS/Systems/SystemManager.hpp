#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <data-types.h>
#include <unordered_map>
#include "System.hpp"


namespace famm {

	class SystemManager
	{
	private:

		std::unordered_map<const char*, Signature> systemSignatures;	//map of names and signatures of defined systems
		std::unordered_map<const char*, std::shared_ptr<System>> systems;				//map of names and pointers to defined systems

	public:

		//add a new system (name and pointer) to the systems map and return a pointer to the system
		template<typename T>
		std::shared_ptr<T> addSystem() {

			//get the system name
			const char* systemName = typeid(T).name();
			assert(systems.find(systemName) == systems.end() && "System already defined.");

			//create a pointer to the system, add the system name and pointer to the systems map, and return the system pointer
			auto sPtr = std::make_shared<T>();
		    //std::shared_ptr<T> sPtr = std::make_shared<T>();
			//T* sPtr = new T;
			systems.insert({ systemName,sPtr });
			return sPtr;
		}								

		//set the signature of a specific system
		template<typename T>
		void setSignature(Signature signature) {

			//get the system name
			const char* systemName = typeid(T).name();
			assert(systems.find(systemName) != systems.end() && "System doesn't exist.");

			//insert system name and signature in the systemSignatures map
			systemSignatures.insert({ systemName,signature });

		}		

		//notify all systems that an entity has been destroyed to remove it from their entities set if exists
		void entityDestroyed(Entity entity) {

			//iterate over the entitiesSet of all systems and erase the destroyed entity if exists
			for (auto& it : systems) it.second->entitiesSet.erase(entity);

		}		

		//notify all systems of the change in the entity signature and take the correct action (add/remove/no change in entities set)
		void entitySignatureChanged(Entity entity, Signature newEntitySignature) {

			//iterate over the entitiesSet of all systems 
			for (auto& it : systems) {
				//if the entity signature matches the system signature (has all components in system signature), add it to the system's entitiesSet
				if ((newEntitySignature & systemSignatures[it.first]) == systemSignatures[it.first])
					it.second->entitiesSet.insert(entity);

				//if the entity's new signature mismatches the system's, remove it from the entitiesSet
				else it.second->entitiesSet.erase(entity);


			}

		}	



	};

}
#endif