#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <data-types.h>
#include <vec3.hpp>
#include <mesh.hpp>
#include <Material.hpp>

namespace famm {
	
	struct Transform {

		glm::vec3 position;		//for translation
		glm::vec3 scale;		//for scaling
		glm::vec3 rotation;		//representing Euler Angles
		Entity parent;			//parent id

	};

	struct MeshRenderer {

		Mesh* M;       // Pointer to the mesh Class
		Material * mat; // pointer to the material class
		




	};






}
#endif