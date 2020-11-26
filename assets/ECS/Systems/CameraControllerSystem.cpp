#include "CameraControllerSystem.hpp"



void famm::CameraControllerSystem::moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, CameraSystem* camsys)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
        auto& transform = ECSmanager->getComponentData<Transform>(entity);

        //glm::vec3 front = camsys->Forward(ECSmanager), up = camsys->Up(ECSmanager), right = camsys->Right(ECSmanager);
        glm::vec3 front = glm::vec3(0,0,0), up = glm::vec3(0, 0, 0), right = glm::vec3(0, 0, 0);

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

        if (deviceManager->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !cameraController.mouse_locked) 
        {
            deviceManager->getMouse().lockMouse(deviceManager->getWindow());
            cameraController.mouse_locked = true;
        }
        else if (!deviceManager->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && cameraController.mouse_locked) 
        {
            deviceManager->getMouse().unlockMouse(deviceManager->getWindow());
            cameraController.mouse_locked = false;
        }

        if (deviceManager->getMouse().isPressed(GLFW_MOUSE_BUTTON_1))
        {
            glm::vec2 delta = deviceManager->getMouse().getMouseDelta();
            pitch -= delta.y * cameraController.pitch_sensitivity;
            yaw -= delta.x * cameraController.yaw_sensitivity;
        }
    }
}