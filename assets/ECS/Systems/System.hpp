#ifndef SYSTEM_H
#define SYSTEM_H

#include <data-types.h>
#include <set>
namespace famm {

	class System
	{
	public:

		std::set<Entity> entitiesSet;		//set of entities that the system works on

	};

}
#endif