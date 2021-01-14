#include "InteractionSystem.hpp"
#include "iostream"

void famm::InteractionSystem::performInteraction(ECSManager* myManager, Entity object,Interaction& component)
{
	if (component.action == 2)
	{
		myManager->destroyEntity(object);
		return;
	}
	if(component.componentType == 0)
	{ 
		if (component.action == 1)
		{
			auto& myLightComponent = myManager->getComponentData<Light>(object);

			myLightComponent.enabled = !myLightComponent.enabled;
		}
	}	
	else if (component.componentType == 1)
	{
		if (component.action == 1)
		{
			auto& myMeshComponent = myManager->getComponentData<MeshRenderer>(object);

			myMeshComponent.enabled = !myMeshComponent.enabled;
		}
	}
}

void famm::InteractionSystem::updateInteractions(ECSManager* myManager, DeviceManager* myDeviceManager,std::shared_ptr<CameraSystem> myCameraSystem)
{
	famm::Camera cameraComponent;
	cameraComponent.enabled = false;
	famm::Entity camera;
	// get active camera
	for (auto& cam: myCameraSystem->entitiesSet)
	{
		cameraComponent = myManager->getComponentData<famm::Camera>(cam);
		if (cameraComponent.enabled)
		{
			camera = cam;
			break;
		}
	}
	if (!cameraComponent.enabled) return;


	std::unordered_set<Entity> copy = entitiesSet;
	for (auto& entity : copy)
	{
		auto& myInteractionComponent = myManager->getComponentData<famm::Interaction>(entity);
		myInteractionComponent.isInteracted = false;
		if (myInteractionComponent.enabled)
		{
			if (myInteractionComponent.parent != 0)
			{
				auto&  parentIneractionComponent = myManager->getComponentData<famm::Interaction>(myInteractionComponent.parent);
				if (parentIneractionComponent.isInteracted)
				{
					performInteraction(myManager, entity, myInteractionComponent);
				}
			}
			else
			{
				
				glm::vec3& cameraPos = myManager->getComponentData<famm::Transform>(camera).position; //Get camera position
				auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);

				float distance = glm::distance(cameraPos, myTransformComponent.position);
				if (myTransformComponent.isLoockedAt && distance <= myInteractionComponent.distanceOfInertaction && myDeviceManager->mouseActionChecker(myInteractionComponent.buttonOfInteraction, famm::PressModes::JUST_PRESSED))
				{
					myInteractionComponent.isInteracted = true;
					if(myInteractionComponent.on == 0 || myInteractionComponent.on == 2)
						performInteraction(myManager, entity, myInteractionComponent);
				}
			}	
		}
	}
}