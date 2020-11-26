#pragma once
#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <memory>
#include <data-types.h>
#include "./System.hpp"
#include "../ECSManager.hpp"
#include "../Components/Components.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace famm {

	class CameraSystem : System
	{
	private:

		glm::mat4 V{}, P{}, VP{};

	public:

		void famm::CameraSystem::setType(bool ProjectionType,  ECSManager* ECSmanager);

        void famm::CameraSystem::setOrthographicSize(float orthographic_height,  ECSManager* ECSmanager);

        void famm::CameraSystem::setVerticalFieldOfView(float field_of_view_y,  ECSManager* ECSmanager);

        void famm::CameraSystem::setAspectRatio(float aspect_ratio,  ECSManager* ECSmanager);

        void famm::CameraSystem::setNearPlane(float near,  ECSManager* ECSmanager);

        void famm::CameraSystem::setFarPlane(float far,  ECSManager* ECSmanager);

        void famm::CameraSystem::setEyePosition(glm::vec3 eye,  ECSManager* ECSmanager);

        void famm::CameraSystem::setDirection(glm::vec3 direction,  ECSManager* ECSmanager);

        void famm::CameraSystem::setTarget(glm::vec3 target,  ECSManager* ECSmanager);

        void famm::CameraSystem::setUp(glm::vec3 up,  ECSManager* ECSmanager);

        void famm::CameraSystem::setVericalFieldOFViewAngle(float vertical_field_of_view_angle,  ECSManager* ECSmanager);

        bool famm::CameraSystem::getType( ECSManager* ECSmanager);

        float famm::CameraSystem::getOrthographicSize( ECSManager* ECSmanager);

        float famm::CameraSystem::getVerticalFieldOfView( ECSManager* ECSmanager);

        float famm::CameraSystem::getAspectRatio( ECSManager* ECSmanager);

        float famm::CameraSystem::getNearPlane( ECSManager* ECSmanager);

        float famm::CameraSystem::getFarPlane( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::getEyePosition( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::getDirection( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::getTarget( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::getUp( ECSManager* ECSmanager);

        float famm::CameraSystem::getVericalFieldOFViewAngle( ECSManager* ECSmanager);

        glm::mat4 famm::CameraSystem::getProjectionMatrix( ECSManager* ECSmanager);

        glm::mat4 famm::CameraSystem::getViewMatrix( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Right( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Left( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Up( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Down( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Forward( ECSManager* ECSmanager);

        glm::vec3 famm::CameraSystem::Backward( ECSManager* ECSmanager);
	};

}
#endif