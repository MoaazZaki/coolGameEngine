#pragma once
#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include <System.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"

namespace famm {

    class LightSystem : public System
    {
    public:
        //Class to collect all lights and keep it
         const int MAX_LIGHT_COUNT;
         LightSystem(const int maxCount=16):MAX_LIGHT_COUNT(maxCount){}
    };

}
#endif