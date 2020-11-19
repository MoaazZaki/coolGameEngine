#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <data-types.h>
#include <queue>
#include <array>
namespace famm {

	class EntityManager {

	private:

		std::queue<Entity> remainingEntities;					//queue of available Ids of uncreated entities
		std::array<Signature, MAX_ENTITIES> entitySignatures;	//array of signatures of every living entity
		uint32_t aliveEntitiesCount;							//count of living entities

	public:

		//fill the remainingEntities queue with entity ids from 0 to MAX_ENTITIES
		EntityManager();

		//Create a new entity by pushing the first available id from the queue
		Entity createEntity();

		//Clear entity signature, add its id to remainingEntities queue, and decrement the number of alive entities
		void destroyEntity(Entity entity);

		//Set entitiy signature
		void setSignature(Entity entity, Signature signature);

		//get entity signature
		Signature getSignature(Entity entity);
		
	};

}
#endif