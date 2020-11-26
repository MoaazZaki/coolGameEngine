#pragma once
#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <memory>
#include <data-types.h>
#include "System.hpp"
#include "../ECSManager.hpp"


namespace famm {

	class CameraSystem : System
	{
	private:

		glm::mat4 V{}, P{}, VP{};

	public:

		void famm::CameraSystem::setType(bool ProjectionType, ECSManager* ECSManager);

        void famm::CameraSystem::setOrthographicSize(float orthographic_height, ECSManager* ECSManager);

        void famm::CameraSystem::setVerticalFieldOfView(float field_of_view_y, ECSManager* ECSManager);

        void famm::CameraSystem::setAspectRatio(float aspect_ratio, ECSManager* ECSManager);

        void famm::CameraSystem::setNearPlane(float near, ECSManager* ECSManager);

        void famm::CameraSystem::setFarPlane(float far, ECSManager* ECSManager);

        void famm::CameraSystem::setEyePosition(glm::vec3 eye, ECSManager* ECSManager);

        void famm::CameraSystem::setDirection(glm::vec3 direction, ECSManager* ECSManager);

        void famm::CameraSystem::setTarget(glm::vec3 target, ECSManager* ECSManager);

        void famm::CameraSystem::setUp(glm::vec3 up, ECSManager* ECSManager);

        void famm::CameraSystem::setVericalFieldOFViewAngle(float vertical_field_of_view_angle, ECSManager* ECSManager);

        bool famm::CameraSystem::getType(ECSManager* ECSManager);

        float famm::CameraSystem::getOrthographicSize(ECSManager* ECSManager);

        float famm::CameraSystem::getVerticalFieldOfView(ECSManager* ECSManager);

        float famm::CameraSystem::getAspectRatio(ECSManager* ECSManager);

        float famm::CameraSystem::getNearPlane(ECSManager* ECSManager);

        float famm::CameraSystem::getFarPlane(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::getEyePosition(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::getDirection(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::getTarget(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::getUp(ECSManager* ECSManager);

        float famm::CameraSystem::getVericalFieldOFViewAngle(ECSManager* ECSManager);

        glm::mat4 famm::CameraSystem::getProjectionMatrix(ECSManager* ECSManager);

        glm::mat4 famm::CameraSystem::getViewMatrix(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Right(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Left(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Up(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Down(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Forward(ECSManager* ECSManager);

        glm::vec3 famm::CameraSystem::Backward(ECSManager* ECSManager);
	};

}
#endif