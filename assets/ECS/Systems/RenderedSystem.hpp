#pragma once
#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H


#include <System.hpp>
#include <DeviceManager.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"


namespace famm {

    class RendererSystem : System
    {
    private:
    public:
        void drawEnities(ECSManager* myManager);

        void updateEntites(ECSManager* myManager);
    };

}
#endif