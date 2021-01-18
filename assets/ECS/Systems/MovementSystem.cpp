#include "MovementSystem.hpp"


void famm::MovementSystem::updateCoordinates(ECSManager* myManager, DeviceManager* myDeviceManager, std::shared_ptr <CameraSystem> myCameraSystem)
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
	
	for (auto& entity : entitiesSet) {
		auto& myMovementComponent = myManager->getComponentData<famm::Movement>(entity);
		if (myMovementComponent.enabled) {
			auto& myCameraTransformComponent = myManager->getComponentData<famm::Transform>(camera);
			auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);

			

			if (myTransformComponent.isLoockedAt && myTransformComponent.distanceToPlayer <= myMovementComponent.distanceOfMoving && myDeviceManager->mouseActionChecker((famm::ControlsActions)0, famm::PressModes::IS_PRESSED))
			{
				std::cout << myTransformComponent.distanceToPlayer << std::endl;
				glm::vec3 diff = myCameraTransformComponent.position - myMovementComponent.lastPos;
				myTransformComponent.position.x += diff.x;
				myTransformComponent.position.z += diff.z;
				myMovementComponent.lastPos = myCameraTransformComponent.position;
			}
			else
			{
				myMovementComponent.lastPos = myCameraTransformComponent.position;
			}
		}
	}
}