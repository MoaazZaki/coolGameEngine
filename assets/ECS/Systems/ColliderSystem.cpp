#include "ColliderSystem.hpp"
#include "iostream"


bool isIntersected(glm::vec3 point, bool isHighCollider, glm::vec3 u, glm::vec3 v, glm::vec3 w, float u_p1_minus_p4, float u_p1_minus_p5, float v_p1_minus_p2, float v_p1_minus_p5, float w_p1_minus_p2, float w_p1_minus_p4)
{
	float u_camera = glm::dot(u, point);
	float v_camera = glm::dot(v, point);
	float w_camera = glm::dot(w, point);

	if (u_camera >= std::min<float>(u_p1_minus_p4, u_p1_minus_p5) && u_camera <= std::max<float>(u_p1_minus_p4, u_p1_minus_p5))
	{
		if (w_camera >= std::min<float>(w_p1_minus_p2, w_p1_minus_p4) && w_camera <= std::max<float>(w_p1_minus_p2, w_p1_minus_p4))
		{
			if (v_camera >= std::min<float>(v_p1_minus_p2, v_p1_minus_p5) && v_camera <= std::max<float>(v_p1_minus_p2, v_p1_minus_p5) || isHighCollider)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


//glm::vec3 getCenter(const glm::vec3& p1_max, const glm::vec3& p1_min)
//{
//	return glm::vec3(fabs(p1_max.x - p1_min.x) / 2, fabs(p1_max.y - p1_min.y) / 2, fabs(p1_max.z - p1_min.z) / 2);
//}
//
//glm::vec3 getExt(const glm::vec3& p1, const glm::vec3& p1_max)
//{
//	return p1 - p1_max;
//}

bool isOverLapped(const glm::vec3 & p1_max, const glm::vec3& p1_min, const glm::vec3& p2_max, const glm::vec3& p2_min)
{
	return (p1_min.x <= p2_max.x && p1_max.x >= p2_min.x) && (p1_min.y <= p2_max.y && p1_max.y >= p2_min.y) && (p1_min.z <= p2_max.z && p1_max.z >= p2_min.z);
}


void famm::ColliderSystem::initializeColliders(ECSManager* myManager)
{
	for (auto& entity: entitiesSet)
	{
		auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);
		auto& myColliderComponent = myManager->getComponentData<famm::Collider>(entity);
		myColliderComponent.lastPos = myTransformComponent.position;
	}
}


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

	for (auto it = entitiesSet.begin() ;  it != entitiesSet.end(); ++it)
	{
		auto& myColliderComponent = myManager->getComponentData<famm::Collider>(*it);
		if (myColliderComponent.enabled)
		{
			// Checking the Collision of player with object

			auto& myTransformComponent = myManager->getComponentData<famm::Transform>(*it);
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

			if(isIntersected(myCameraTransformComponent.position, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
				myCameraTransformComponent.position = myColliderComponent.lastNonCollided;
			else
				myColliderComponent.lastNonCollided = myCameraTransformComponent.position;

			


			// Cheking if object collides with another
			if (myColliderComponent.lastPos != myTransformComponent.position)
			{
				for (auto other = entitiesSet.begin(); other != entitiesSet.end(); ++other)
				{
					if (*other == *it) continue;

					auto& otherTransformComponent = myManager->getComponentData<famm::Transform>(*other);
					auto& otherColliderComponent = myManager->getComponentData<famm::Collider>(*other);

					glm::vec4 otherPointMin = otherTransformComponent.to_mat4() * glm::vec4(otherColliderComponent.AABBcorners[0], 1.0);
					glm::vec4 otherPointMax = otherTransformComponent.to_mat4() * glm::vec4(otherColliderComponent.AABBcorners[1], 1.0);
					// Check if the two AABB intersects

					//std::cout << p2_c.x << "," << p2_c.y << "," << p2_c.z << std::endl;
					if (!isOverLapped(pointMax, pointMin, otherPointMax, otherPointMin)) continue;

					myTransformComponent.position = myColliderComponent.lastPos;
					break;
				}
						
				myColliderComponent.lastPos = myTransformComponent.position;
			}

		}

	}
}


/*float u_camera = glm::dot(u, myCameraTransformComponent.position);
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
			}*/




			











//
//glm::vec3 otherPointCenter = otherTransformComponent.position;
//
////std::cout << "--------------------------------------------------" << std::endl;
//
//
//glm::vec3 face = otherPointCenter;
////std::cout << face.x << "-" << face.y << "-" << face.z << "-" << std::endl;
//
//face.x = otherPointCenter.x - (otherPointMin.x / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//face = otherPointCenter;
//face.x = otherPointCenter.x + (otherPointMin.x / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//face = otherPointCenter;
//face.z = otherPointCenter.z - (otherPointMin.z / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//face = otherPointCenter;
//face.z = otherPointCenter.z + (otherPointMin.z / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//face = otherPointCenter;
//face.y = otherPointCenter.y - (otherPointMin.y / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//face = otherPointCenter;
//face.y = otherPointCenter.y + (otherPointMin.y / 2);
//
//if (!isIntersected(face, myColliderComponent.highCollider, u, v, w, u_p1_minus_p4, u_p1_minus_p5, v_p1_minus_p2, v_p1_minus_p5, w_p1_minus_p2, w_p1_minus_p4))
//continue;
//
//myTransformComponent.position = myColliderComponent.lastPos;
//break;
//				}
//				myColliderComponent.lastPos = myTransformComponent.position;