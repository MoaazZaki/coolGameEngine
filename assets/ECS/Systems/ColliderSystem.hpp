#ifndef COLLIDERSYSTEM_H
#define COLLIDERSYSTEM_H

#include <System.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"
#include <CameraSystem.hpp>
#include <DeviceManager.hpp>
namespace famm {

    class ColliderSystem : public System
    {
    public:

        void updateColliders(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem);
    };

}
#endif