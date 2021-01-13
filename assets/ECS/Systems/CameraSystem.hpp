#pragma once
#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <memory>
#include <data-types.h>
#include "./System.hpp"
#include "../ECSManager.hpp"
#include "../Components/Components.hpp"


namespace famm {

	class CameraSystem : public System
	{
	private:

		glm::mat4 V{}, P{}, VP{};

	public:

		void setType(bool ProjectionType,  ECSManager* ECSmanager,Entity activeCamera);

        void setOrthographicSize(float orthographic_height,  ECSManager* ECSmanager,Entity activeCamera);

        void setVerticalFieldOfView(float field_of_view_y,  ECSManager* ECSmanager,Entity activeCamera);

        void setAspectRatio(float aspect_ratio,  ECSManager* ECSmanager,Entity activeCamera);

        void setNearPlane(float near,  ECSManager* ECSmanager,Entity activeCamera);

        void setFarPlane(float far,  ECSManager* ECSmanager,Entity activeCamera);

        void setYaw(float yaw, ECSManager* ECSmanager,Entity activeCamera);
        
        void setPitch(float pitch, ECSManager* ECSmanager,Entity activeCamera);

        //void setEyePosition(glm::vec3 eye,  ECSManager* ECSmanager,Entity activeCamera);

        void setDirection(glm::vec3 direction,  ECSManager* ECSmanager,Entity activeCamera);

        void setTarget(glm::vec3 target,  ECSManager* ECSmanager,Entity activeCamera);

        //void setUp(glm::vec3 up,  ECSManager* ECSmanager,Entity activeCamera);

        void setVericalFieldOFViewAngle(float vertical_field_of_view_angle,  ECSManager* ECSmanager,Entity activeCamera);

        bool getType( ECSManager* ECSmanager,Entity activeCamera);

        float getOrthographicSize( ECSManager* ECSmanager,Entity activeCamera);

        float getVerticalFieldOfView( ECSManager* ECSmanager,Entity activeCamera);

        float getAspectRatio( ECSManager* ECSmanager,Entity activeCamera);

        float getNearPlane( ECSManager* ECSmanager,Entity activeCamera);

        float getFarPlane( ECSManager* ECSmanager,Entity activeCamera);

        float getYaw(ECSManager* ECSmanager,Entity activeCamera);

        float getPitch(ECSManager* ECSmanager,Entity activeCamera);

        //glm::vec3 getEyePosition( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 getDirection( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 getTarget( ECSManager* ECSmanager,Entity activeCamera);

        //glm::vec3 getUp( ECSManager* ECSmanager,Entity activeCamera);

        float getVericalFieldOFViewAngle( ECSManager* ECSmanager,Entity activeCamera);

        glm::mat4 getProjectionMatrix( ECSManager* ECSmanager,Entity activeCamera);

        glm::mat4 getViewMatrix( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Right( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Left( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Up( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Down( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Forward( ECSManager* ECSmanager,Entity activeCamera);

        glm::vec3 Backward( ECSManager* ECSmanager,Entity activeCamera);
	};

}
#endif