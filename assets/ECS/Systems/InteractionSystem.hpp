#ifndef INTERACTIONSYSTEM_H
#define INTERACTIONSYSTEM_H

#include <System.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"
#include <LightSystem.hpp>
#include <CameraSystem.hpp>
#include <DeviceManager.hpp>
namespace famm {

    class InteractionSystem : public System
    {
    public:
        void performInteraction(ECSManager* myManager, Entity object, Interaction& component);
        void updateInteractions(ECSManager* myManager, DeviceManager* myDeviceManager, std::shared_ptr<CameraSystem> myCameraSystem, std::shared_ptr<LightSystem> myLightSystem);
    };

}
#endif