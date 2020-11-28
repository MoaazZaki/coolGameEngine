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

		void setType(bool ProjectionType,  ECSManager* ECSmanager);

        void setOrthographicSize(float orthographic_height,  ECSManager* ECSmanager);

        void setVerticalFieldOfView(float field_of_view_y,  ECSManager* ECSmanager);

        void setAspectRatio(float aspect_ratio,  ECSManager* ECSmanager);

        void setNearPlane(float near,  ECSManager* ECSmanager);

        void setFarPlane(float far,  ECSManager* ECSmanager);

        void setYaw(float yaw, ECSManager* ECSmanager);
        
        void setPitch(float pitch, ECSManager* ECSmanager);

        /*void setEyePosition(glm::vec3 eye,  ECSManager* ECSmanager);

        void setDirection(glm::vec3 direction,  ECSManager* ECSmanager);

        void setTarget(glm::vec3 target,  ECSManager* ECSmanager);

        void setUp(glm::vec3 up,  ECSManager* ECSmanager);*/

        void setVericalFieldOFViewAngle(float vertical_field_of_view_angle,  ECSManager* ECSmanager);

        bool getType( ECSManager* ECSmanager);

        float getOrthographicSize( ECSManager* ECSmanager);

        float getVerticalFieldOfView( ECSManager* ECSmanager);

        float getAspectRatio( ECSManager* ECSmanager);

        float getNearPlane( ECSManager* ECSmanager);

        float getFarPlane( ECSManager* ECSmanager);

        float getYaw(ECSManager* ECSmanager);

        float getPitch(ECSManager* ECSmanager);

        /*glm::vec3 getEyePosition( ECSManager* ECSmanager);

        glm::vec3 getDirection( ECSManager* ECSmanager);

        glm::vec3 getTarget( ECSManager* ECSmanager);

        glm::vec3 getUp( ECSManager* ECSmanager);*/

        float getVericalFieldOFViewAngle( ECSManager* ECSmanager);

        glm::mat4 getProjectionMatrix( ECSManager* ECSmanager);

        glm::mat4 getViewMatrix( ECSManager* ECSmanager);

        glm::vec3 Right( ECSManager* ECSmanager);

        glm::vec3 Left( ECSManager* ECSmanager);

        glm::vec3 Up( ECSManager* ECSmanager);

        glm::vec3 Down( ECSManager* ECSmanager);

        glm::vec3 Forward( ECSManager* ECSmanager);

        glm::vec3 Backward( ECSManager* ECSmanager);
	};

}
#endif