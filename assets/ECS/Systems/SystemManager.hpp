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
		std::unordered_map<const char*, System*> systems;				//map of names and pointers to defined systems

	public:

		template<typename T>
		T* addSystem();								//add a new system (name and pointer) to the systems map and return a pointer to the system

		template<typename T>
		void setSignature(Signature signature);		//set the signature of a specific system

		void entityDestroyed(Entity entity);		//notify all systems that an entity has been destroyed to remove it from their entities set if exists

		void entitySignatureChanged(Entity entity, Signature newEntitySignature);	//notify all systems of the change in the entity signature and take the correct
																				//action (add/remove/no change in entities set)

	};

}
#endif