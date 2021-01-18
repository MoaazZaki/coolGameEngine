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
        void initializeColliders(ECSManager* myManager);
        //bool isIntersected(glm::vec3 point, bool isHighCollider, glm::vec3 u, glm::vec3 v, glm::vec3 w, float u_p1_minus_p4, float u_p1_minus_p5, float v_p1_minus_p2, float v_p1_minus_p5, float w_p1_minus_p2, float w_p1_minus_p4);
        void updateColliders(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem);
    };

}
#endif