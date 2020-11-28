#include "CameraControllerSystem.hpp"



void famm::CameraControllerSystem::moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, std::shared_ptr<CameraSystem> camsys)
{
    for (auto const& entity : entitiesSet)
    {
        
        auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
        auto& camera = ECSmanager->getComponentData<Camera>(cameraController.controlledCamera);
        auto& transform = ECSmanager->getComponentData<Transform>(cameraController.controlledCamera);



        if (deviceManager->pressedActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED) && !cameraController.mouse_locked)
        {
            deviceManager->getMouse().lockMouse(deviceManager->getWindow());
            cameraController.mouse_locked = true;
        }
        else if (!deviceManager->pressedActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED) && cameraController.mouse_locked)
        {
            deviceManager->getMouse().unlockMouse(deviceManager->getWindow());
            cameraController.mouse_locked = false;
        }

        if (deviceManager->pressedActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED))
        {
            glm::vec2 delta = deviceManager->getMouse().getMouseDelta();
            camera.pitch -= delta.y * cameraController.pitch_sensitivity;
            camera.yaw -= delta.x * cameraController.yaw_sensitivity;
        }

        glm::vec3 front = camsys->Forward(ECSmanager), up = camsys->Up(ECSmanager), right = camsys->Right(ECSmanager);


        if (deviceManager->pressedActionChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED))
            transform.position += front * ((float)delta_time * cameraController.position_sensitivity.z);
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED))
            transform.position -= front * ((float)delta_time * cameraController.position_sensitivity.z);
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED))
            transform.position -= right * ((float)delta_time * cameraController.position_sensitivity.x);
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
            transform.position += right * ((float)delta_time * cameraController.position_sensitivity.x);
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_UP, famm::PressModes::IS_PRESSED))
            transform.position += front * ((float)delta_time * cameraController.position_sensitivity.x);
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_DOWN, famm::PressModes::IS_PRESSED))
            transform.position -= front * ((float)delta_time * cameraController.position_sensitivity.x);
    }
}