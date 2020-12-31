#ifndef SYSTEM_H
#define SYSTEM_H

#include <data-types.h>
#include <unordered_set>
namespace famm {

	class System
	{
	public:

		std::unordered_set<Entity> entitiesSet;		//set of entities that the system works on

	};

}
#endif