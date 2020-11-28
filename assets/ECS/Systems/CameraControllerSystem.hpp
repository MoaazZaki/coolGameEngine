#pragma once
#ifndef CAMERACONTROLLERSYSTEM_H
#define CAMERACONTROLLERSYSTEM_H


#include <System.hpp>
#include <DeviceManager.hpp>
#include <CameraSystem.hpp>


namespace famm {

    class CameraControllerSystem : public System
    {
    private:
    public:
        void moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, std::shared_ptr<CameraSystem> camera);
    };

}
#endif