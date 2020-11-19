#ifndef COMPONENTARRAYINTERFACE_H
#define COMPONENTARRAYINTERFACE_H

#include <data-types.h>

namespace famm {

	class ComponentArrayInterface {
		
	public:

		virtual ~ComponentArrayInterface() = default;		//default destructor
		virtual void entityDestroyed(Entity entity) = 0;	//remove destroyed entity data from all types of componentarrays

	};
}
#endif