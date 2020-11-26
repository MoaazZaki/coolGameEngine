#include "CameraControllerSystem.hpp"
#include "../ECSManager.hpp"
#include "../Components/Components.hpp"


void famm::CameraControllerSystem::moveCamera(ECSManager* ECSManager, DeviceManager* deviceManager, double delta_time, CameraSystem* camsys)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);

        /*auto& transform = ECSManager->getComponentData<Transform>(entity);*/

        glm::vec3 front = camsys->Forward(ECSManager), up = camsys->Up(ECSManager), right = camsys->Right(ECSManager);

        if (deviceManager->pressChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye += front * ((float)delta_time * cameraController.position_sensitivity.z);
            }
        }
        else if (deviceManager->pressChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye -= front * ((float)delta_time * cameraController.position_sensitivity.z);
            }
        }
        else if (deviceManager->pressChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye -= right * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }
        else if (deviceManager->pressChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye += right * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }
       /* else if (deviceManager->pressChecker(famm::ControlsActions::, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye += right * ((float)delta_time * current_sensitivity.x);
            }
        }
        else if (deviceManager->pressChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSManager->getComponentData<Camera>(entity);
                auto& cameraController = ECSManager->getComponentData<CameraController>(entity);
                camera.eye += right * ((float)delta_time * current_sensitivity.x);
            }
        }*/

    }
}