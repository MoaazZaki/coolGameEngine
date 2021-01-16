#include "ColliderSystem.hpp"
#include "iostream"

void famm::ColliderSystem::updateColliders(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem)
{
	famm::Camera cameraComponent;
	cameraComponent.enabled = false;
	famm::Entity camera;
	// get active camera
	for (auto& cam : myCameraSystem->entitiesSet)
	{
		cameraComponent = myManager->getComponentData<famm::Camera>(cam);
		if (cameraComponent.enabled)
		{
			camera = cam;
			break;
		}
	}
	if (!cameraComponent.enabled) return;

	for (auto& entity : entitiesSet)
	{
		auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);
		auto& myColliderComponent = myManager->getComponentData<famm::Collider>(entity);
		auto& myCameraTransformComponent = myManager->getComponentData<famm::Transform>(camera);

		glm::vec4 pointMin = myTransformComponent.to_mat4() * glm::vec4(myColliderComponent.AABBcorners[0], 1.0);
		glm::vec4 pointMax = myTransformComponent.to_mat4() * glm::vec4(myColliderComponent.AABBcorners[1], 1.0);
		
		glm::vec3 p1 = glm::vec3({ pointMin.x - 1,pointMin.y - 1,pointMin.z - 1 });
		glm::vec3 p2 = glm::vec3({ pointMax.x + 1,pointMin.y - 1,pointMin.z - 1 });
		glm::vec3 p4 = glm::vec3({ pointMin.x - 1,pointMax.y + 1,pointMin.z - 1 });
		glm::vec3 p5 = glm::vec3({ pointMin.x - 1,pointMin.y - 1,pointMax.z + 1 });

		glm::vec3 p1_minus_p4 = p1 - p4;
		glm::vec3 p1_minus_p5 = p1 - p5;
		glm::vec3 p1_minus_p2 = p1 - p2;

		glm::vec3 u = p1_minus_p2;
		glm::vec3 v = p1_minus_p4;
		glm::vec3 w = p1_minus_p5;

		float u_p1_minus_p4 = glm::dot(u, p1);
		float u_p1_minus_p5 = glm::dot(u, p2);
		float v_p1_minus_p2 = glm::dot(v, p1);
		float v_p1_minus_p5 = glm::dot(v, p4);
		float w_p1_minus_p2 = glm::dot(w, p1);
		float w_p1_minus_p4 = glm::dot(w, p5);
		float u_camera = glm::dot(u, myCameraTransformComponent.position);
		float v_camera = glm::dot(v, myCameraTransformComponent.position);
		float w_camera = glm::dot(w, myCameraTransformComponent.position);

		if (u_camera >= std::min<float>(u_p1_minus_p4, u_p1_minus_p5) && u_camera <= std::max<float>(u_p1_minus_p4, u_p1_minus_p5))
		{
			if (w_camera >= std::min<float>(w_p1_minus_p2, w_p1_minus_p4) && w_camera <= std::max<float>(w_p1_minus_p2, w_p1_minus_p4))
			{
				if (v_camera >= std::min<float>(v_p1_minus_p2, v_p1_minus_p5) && v_camera <= std::max<float>(v_p1_minus_p2, v_p1_minus_p5) || myColliderComponent.highCollider)
				{
					myCameraTransformComponent.position = myColliderComponent.lastNonCollided;
				}
				else
				{
					myColliderComponent.lastNonCollided = myCameraTransformComponent.position;
				}
			}
			else
			{
				myColliderComponent.lastNonCollided = myCameraTransformComponent.position;
			}
		}
		else
		{
			myColliderComponent.lastNonCollided = myCameraTransformComponent.position;
		}
	}
}
