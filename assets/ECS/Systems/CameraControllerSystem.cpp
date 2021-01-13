#include "CameraControllerSystem.hpp"

void famm::CameraControllerSystem::shakeCamera(double &hieght,const double &delta_time)
{
    static float amplitude = 0.1f;
    static float adjustAmplitudePerSecond = 0.01f;
    static float timeElapsed = 0.0f;

    
    timeElapsed += delta_time;
    //amplitude += adjustAmplitudePerSecond * delta_time;
    hieght += (double)amplitude * glm::sin(timeElapsed*10);
  
}

void famm::CameraControllerSystem::moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, std::shared_ptr<CameraSystem> camsys)
{
    for (auto const& entity : entitiesSet)
    {
        
        auto& cameraController = ECSmanager->getComponentData<CameraController>(entity);
        auto& camera = ECSmanager->getComponentData<Camera>(cameraController.controlledCamera);
        auto& transform = ECSmanager->getComponentData<Transform>(cameraController.controlledCamera);
        Entity cameraEntity = cameraController.controlledCamera;

        if (cameraEntity == 8)
        {

            if (deviceManager->mouseActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED) && !cameraController.mouse_locked)
            {
                deviceManager->getMouse().lockMouse(deviceManager->getWindow());
                cameraController.mouse_locked = true;
            }
            else if (!deviceManager->mouseActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED) && cameraController.mouse_locked)
            {
                deviceManager->getMouse().unlockMouse(deviceManager->getWindow());
                cameraController.mouse_locked = false;
            }



            if (deviceManager->mouseActionChecker(famm::ControlsActions::MOUSE_LEFT, famm::PressModes::IS_PRESSED))
            {
                glm::vec2 delta = deviceManager->getMouse().getMouseDelta();
                camera.pitch -= delta.y * cameraController.pitch_sensitivity;
                camera.yaw -= delta.x * cameraController.yaw_sensitivity;
            }

            glm::vec3 front = camsys->Forward(ECSmanager, cameraEntity), up = camsys->Up(ECSmanager, cameraEntity), right = camsys->Right(ECSmanager, cameraEntity);

            glm::vec3 currentSensitivity = cameraController.position_sensitivity;
            if (deviceManager->pressedActionChecker(famm::ControlsActions::SPRINT, famm::PressModes::IS_PRESSED)) currentSensitivity *= cameraController.speedup_factor;



            if (deviceManager->pressedActionChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED))
                transform.position += front * ((float)delta_time * currentSensitivity.z);
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED))
                transform.position -= front * ((float)delta_time * currentSensitivity.z);
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED))
                transform.position -= right * ((float)delta_time * currentSensitivity.x);
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
                transform.position += right * ((float)delta_time * currentSensitivity.x);
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_UP, famm::PressModes::IS_PRESSED))
                transform.position += up * ((float)delta_time * currentSensitivity.x);
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::CAMERA_DOWN, famm::PressModes::IS_PRESSED))
                transform.position -= up * ((float)delta_time * currentSensitivity.x);

            transform.rotation = glm::vec3(glm::cos(camera.yaw), 0, -glm::sin(camera.yaw)) * glm::cos(camera.pitch) + glm::vec3(0, glm::sin(camera.pitch), 0);
        }
        else
        {
           
            deviceManager->getMouse().lockMouse(deviceManager->getWindow());
            glm::vec2 delta = deviceManager->getMouse().getMouseDelta();
            if (camera.pitch <= 1.49 && camera.pitch >= -1.49)
                camera.pitch -= delta.y * cameraController.pitch_sensitivity;
            else if(camera.pitch > 1.49)
                camera.pitch = 1.489;
            else if (camera.pitch < -1.49)
                camera.pitch = -1.489;
            camera.yaw -= delta.x * cameraController.yaw_sensitivity;
            

            glm::vec3 front = camsys->Forward(ECSmanager, cameraEntity), up = camsys->Up(ECSmanager, cameraEntity), right = camsys->Right(ECSmanager, cameraEntity);

            glm::vec3 currentSensitivity = cameraController.position_sensitivity;
            if (deviceManager->pressedActionChecker(famm::ControlsActions::SPRINT, famm::PressModes::IS_PRESSED)) currentSensitivity *= cameraController.speedup_factor;

            double hieght = transform.position.y;
            if (deviceManager->pressedActionChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED))
            {
                transform.position += front * ((float)delta_time * currentSensitivity.z);
                shakeCamera(hieght, delta_time);
            }
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED))
            {
                transform.position -= front * ((float)delta_time * currentSensitivity.z);
                shakeCamera(hieght, delta_time);
            }
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED))
            {
                transform.position -= right * ((float)delta_time * currentSensitivity.x);
                shakeCamera(hieght, delta_time);
            }
            else if (deviceManager->pressedActionChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED))
            {
                transform.position += right * ((float)delta_time * currentSensitivity.x);
                shakeCamera(hieght, delta_time);
            }
            transform.position.y = hieght;
            

            transform.rotation = glm::vec3(glm::cos(camera.yaw), 0, -glm::sin(camera.yaw)) * glm::cos(camera.pitch) + glm::vec3(0, glm::sin(camera.pitch), 0);
        }
    }
}