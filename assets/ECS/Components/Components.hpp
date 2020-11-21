#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <data-types.h>
#include <vec3.hpp>

namespace famm {
	
	struct Transform {

		glm::vec3 position;		//for translation
		glm::vec3 scale;		//for scaling
		glm::vec3 rotation;		//representing Euler Angles
		Entity parent;			//parent id

	};

}
#endif