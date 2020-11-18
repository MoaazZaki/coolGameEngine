#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include <ComponentArrayInterface.hpp>
#include <unordered_map>
#include <data-types.h>

namespace famm {

	template<typename T>
	class ComponentArray : public ComponentArrayInterface {

	private:

		std::array<T, MAX_ENTITIES> componentArray;			//array of size MAX_ENTITIES holding the current component values for relevant entities
		std::unordered_map<Entity, size_t> entityIndexMap;	//mapping current entity ids to the componentarray indices 
		std::unordered_map<size_t, Entity> indexEntityMap;	//mapping componentarray indices to current entity ids
		size_t entriesCount;								//number of valid entries in the componentarray

	public:

		ComponentArray();									//constructor: set entriesCount to 0
		void addData(Entity entity, T componentdata);		//insert component data of entity in the componentarray
		void removeData(Entity entity);	//remove component data of entity from the componentarray
		T& getData(Entity entity);							//get the component data of a specific entity
		void entityDestroyed(Entity entity) override;		//remove destroyed entity data from the componentarray

	};

}
#endif