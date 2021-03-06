#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <data-types.h>
#include <glm/vec3.hpp>
#include "./mesh/mesh.hpp"
#include "./mesh/Material.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <DeviceManager.hpp>

namespace famm {

	enum class LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	struct Transform {

		glm::vec3 position;		//for translation
		glm::vec3 scale;		//for scaling
		glm::vec3 rotation;		//representing Euler Angles
		Entity parent;			//parent id
		bool isLoockedAt = false;
		float distanceToPlayer;
		Transform(
			const glm::vec3& position = { 0,0,0 },
			const glm::vec3& rotation = { 0,0,0 },
			const glm::vec3& scale = { 1,1,1 },
			Entity parent = 0
		) : position(position), rotation(rotation), scale(scale), parent(parent) {}

		glm::mat4 to_mat4() const {
			return glm::translate(glm::mat4(1.0f), position) *
				glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
				glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct MeshRenderer {
		bool enabled;
		Mesh* mesh;							// Pointer to the mesh Class
		Material* material;				// pointer to the material class
		glm::vec4 tint = { 1,1,1,1 };		//tint color
	};

	struct Camera {

		bool enabled;
		bool mode;// 0 play - 1 dev
 		//Entity containerEntity;
		bool projectionType;    //Projection type: 0 for Orthographic -- 1 for Perspective 
		glm::vec3 target;
		float near, far;       //distances from camera        
		float aspect_ratio;    //used for calculating the position of the left and right plates
		float vertical_field_of_view_angle;   //for perspective projection
		float orthographic_height;   //for orthographic projection
		float field_of_view_y;
		float yaw, pitch;
	};
	struct CameraController {
		Entity controlledCamera;
		glm::vec3 position_sensitivity;
		float yaw_sensitivity;
		float pitch_sensitivity;
		float fov_sensitivity;
		float speedup_factor;
		bool mouse_locked;
	};
	struct RenderState {
		//Culling
		bool cullingEnabled = true;
		GLuint cullingFrontFace = GL_CCW;
		GLuint cullingFaceToCull = GL_BACK;
		//Blending
		bool blendingEnabled = false; //To check for transparency 
		GLuint blendEquation = GL_FUNC_ADD;
		GLuint blendSourceFactor = GL_SRC_ALPHA;
		GLuint blendDestFactor = GL_ONE_MINUS_SRC_ALPHA;
		glm::vec4 blendColor = { 1.0f,1.0f,1.0f,1.0f };
		//Depth testing
		bool depthEnabled = true;
		GLuint depthFunction = GL_LEQUAL;
		bool transparentDepthEnabled = true; //Write or not
		//Alpha testing
		bool alphaTestingEnabled = true;
		float alphaTestingThreshold = 0.0;
		bool alphaToCoverageEnabled = false;
	};

	struct Light {
		bool enabled;
		//directional,spotlight,point
		LightType type;
		glm::vec3 color;

		//point&spotlight
		float constantAttenuation=0.0;
		float LinearAttenuation = 0.0;
		float QuadraticAttenuation = 0.0;
		//spotlight
		float InnerSpotAngle = 0.0;
		float OuterSpotAngle = 0.0;
	};

	struct Interaction
	{
		Entity parent;//
		bool enabled;//

		bool isOneTime;

		float distanceOfInteraction;//
		GLbyte on; // 0 self - 1 other - 2 both
		GLbyte action; // 0 nothing - 1 toggle - 2 remove 
		GLbyte componentType; // 0 light - 1 mesh
		bool isInteracted = false;

		bool startOn = 0; // 0 button - 1 progress

		bool fireProgress = false;
		int firedProgressIndex;
		GLbyte firingType; // 0 increment - 1 progress finished - 2 all finished


		famm::ControlsActions buttonOfInteraction;

	};

	struct Collider
	{
		bool enabled;
		glm::vec3 AABBcorners[2];		//Bounding box corners
		glm::vec3 lastNonCollided;
		bool highCollider =true;

		glm::vec3 lastPos;
	};

	struct Progress
	{
		GLubyte counter = 0;
		GLubyte goal;
		GLubyte conditionOfInteraction = 0;
		std::vector<int> attachedTo;
	};

	struct Movement
	{
		bool enabled;
		float distanceOfMoving = 50;
		glm::vec3 lastPos;
	};
}

#endif