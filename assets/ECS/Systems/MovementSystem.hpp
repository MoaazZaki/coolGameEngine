#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <System.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"
#include <CameraSystem.hpp>
#include <DeviceManager.hpp>
namespace famm {

    class MovementSystem : public System
    {
    public:
        void updateCoordinates(ECSManager* myManager,DeviceManager* myDeviceManager, std::shared_ptr <CameraSystem>myCameraSystem);
    };

}
#endif