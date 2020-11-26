#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <data-types.h>
#include <glm/vec3.hpp>
#include "./mesh/mesh.hpp"
#include "./mesh/Material.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace famm {
	
	struct Transform {

		glm::vec3 position;		//for translation
		glm::vec3 scale;		//for scaling
		glm::vec3 rotation;		//representing Euler Angles
		Entity parent;			//parent id

		glm::mat4 to_mat4() const {
			return glm::translate(glm::mat4(1.0f), position) *
				glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
				glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct MeshRenderer {

		Mesh* mesh;       // Pointer to the mesh Class
		Material * material; // pointer to the material class
	};

	struct Camera {

		Entity parent;
		bool projectionType;    //Projection type: 0 for Orthographic -- 1 for Perspective 
		glm::vec3 eye;
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 target;
		float near, far;       //distances from camera        
		float aspect_ratio;    //used for calculating the position of the left and right plates
		float vertical_field_of_view_angle;   //for perspective projection
		float orthographic_height;   //for orthographic projection
		float field_of_view_y;
	};
	struct CameraController {
		Entity parent;
		glm::vec3 position_sensitivity;
	};
}
#endif