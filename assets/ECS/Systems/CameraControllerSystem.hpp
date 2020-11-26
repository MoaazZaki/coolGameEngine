#pragma once
#ifndef CAMERACONTROLLERSYSTEM_H
#define CAMERACONTROLLERSYSTEM_H

#include <memory>
#include <data-types.h>
#include "System.hpp"
#include "../ECSManager.hpp"
#include "../../../source/common/DeviceManager.hpp"
#include "../Components/Components.hpp"
#include "./CameraSystem.hpp"




namespace famm {

    class CameraControllerSystem : System
    {
    private:
    public:

        void moveCamera(ECSManager* ECSmanager, DeviceManager* deviceManager, double delta_time, CameraSystem* camera);
    };

}
#endif