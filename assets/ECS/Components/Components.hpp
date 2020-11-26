#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <data-types.h>
#include <glm/vec3.hpp>
#include "./mesh/mesh.hpp"
#include "./mesh/Material.hpp"

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

	struct Camera {

		Entity* containerEntity;
		bool projectionType;    //Projection type: 0 for Orthographic -- 1 for Perspective 
		//glm::vec3 eye;
		//glm::vec3 direction;
		//glm::vec3 up;
		//glm::vec3 target;
		float near, far;       //distances from camera        
		float aspect_ratio;    //used for calculating the position of the left and right plates
		float vertical_field_of_view_angle;   //for perspective projection
		float orthographic_height;   //for orthographic projection
		float field_of_view_y;
	};
	struct CameraController {
		Entity* containerEntity;
		glm::vec3 position_sensitivity;
		float yaw_sensitivity;
		float pitch_sensitivity;
		float fov_sensitivity;
		bool mouse_locked;
	};
}
#endif