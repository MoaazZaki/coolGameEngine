#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <data-types.h>
namespace famm {

	class EntityManager
	{
	private:


	public:
		EntityManager() {}

		Entity CreateEntity() {}

		void DestroyEntity(Entity entity){}

		void SetSignature(Entity entity, Signature signature){}

		Signature GetSignature(Entity entity){}

		
	};

}
#endif