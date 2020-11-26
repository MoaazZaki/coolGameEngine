#include "CameraControllerSystem.hpp"
#include "../ECSManager.hpp"
#include "../Components/Components.hpp"


void famm::CameraControllerSystem::moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, CameraSystem* camsys)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);

        /*auto& transform = ECSmanager->getComponentData<Transform>(entity);*/

        glm::vec3 front = camsys->Forward(ECSmanager), up = camsys->Up(ECSmanager), right = camsys->Right(ECSmanager);

        if (deviceManager->pressedActionChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye += front * ((float)delta_time * cameraController.position_sensitivity.z);
            }
        }
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye -= front * ((float)delta_time * cameraController.position_sensitivity.z);
            }
        }
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye -= right * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye += right * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_UP, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye += front * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_DOWN, famm::PressModes::IS_PRESSED))
        {
            for (auto const& entity : entitiesSet)
            {
                auto& camera = ECSmanager->getComponentData<Camera>(entity);
                auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
                camera.eye -= front * ((float)delta_time * cameraController.position_sensitivity.x);
            }
        }

    }
}