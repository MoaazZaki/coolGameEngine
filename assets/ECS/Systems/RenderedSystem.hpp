#pragma once
#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H

#include <vector>
#include <System.hpp>
#include <DeviceManager.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"
#include "../Systems/CameraSystem.hpp"

namespace famm {

    class RendererSystem : public System
    {
    private:
    public:
        void drawEnities(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem);

        void updateEntites(ECSManager* myManager);

        void cleanEntities(ECSManager* myManager);
    };

}
#endif