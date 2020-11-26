
#include "CameraSystem.hpp"
#include "../ECSManager.hpp"
#include "../Components/Components.hpp"
#include <glm/gtc/matrix_transform.hpp>


void famm::CameraSystem::setType(bool projectionType, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.projectionType = projectionType;
    }
}

void famm::CameraSystem::setOrthographicSize(float orthographic_height, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.orthographic_height = orthographic_height;
    }
}

void famm::CameraSystem::setVerticalFieldOfView(float field_of_view_y, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.field_of_view_y = field_of_view_y;
    }
}

void famm::CameraSystem::setAspectRatio(float aspect_ratio, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.aspect_ratio = aspect_ratio;
    }
}

void famm::CameraSystem::setNearPlane(float near, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.near = near;
    }
}

void famm::CameraSystem::setFarPlane(float far, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.far = far;
    }
}

void famm::CameraSystem::setEyePosition(glm::vec3 eye, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.eye = eye;
    }
}

void famm::CameraSystem::setDirection(glm::vec3 direction, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.direction = direction;
    }
}

void famm::CameraSystem::setTarget(glm::vec3 target, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.target = target;
    }
}

void famm::CameraSystem::setUp(glm::vec3 up, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.up = up;
    }
}

void famm::CameraSystem::setVericalFieldOFViewAngle(float vertical_field_of_view_angle, ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.vertical_field_of_view_angle = vertical_field_of_view_angle;
    }
}

bool famm::CameraSystem::getType(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.projectionType;
    }
}

float famm::CameraSystem::getOrthographicSize(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.orthographic_height;
    }
}

float famm::CameraSystem::getVerticalFieldOfView(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.field_of_view_y;
    }
}

float famm::CameraSystem::getAspectRatio(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.aspect_ratio;
    }
}

float famm::CameraSystem::getNearPlane(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.near;
    }
}

float famm::CameraSystem::getFarPlane(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.far;
    }
}

glm::vec3 famm::CameraSystem::getEyePosition(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.eye;
    }
}

glm::vec3 famm::CameraSystem::getDirection(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.direction;
    }
}

glm::vec3 famm::CameraSystem::getTarget(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.target;
    }
}

glm::vec3 famm::CameraSystem::getUp(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.up;
    }
}

float famm::CameraSystem::getVericalFieldOFViewAngle(ECSManager* ECSManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        return camera.vertical_field_of_view_angle;
    }
}

glm::mat4 famm::CameraSystem::getProjectionMatrix(ECSManager* ECSManager) {

    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        camera.vertical_field_of_view_angle;
        if (camera.projectionType == 0) {
            float half_height = camera.orthographic_height * 0.5f;
            float half_width = camera.aspect_ratio * half_height;
            P = glm::ortho(-half_width, half_width, -half_height, half_height, camera.near, camera.far);
        }
        else {
            P = glm::perspective(camera.field_of_view_y, camera.aspect_ratio, camera.near, camera.far);
        }
        return P;
    }
}

glm::mat4 famm::CameraSystem::getViewMatrix(ECSManager* ECSManager) {

    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSManager->getComponentData<Camera>(entity);
        V = glm::lookAt(camera.eye, camera.eye + camera.direction, camera.up);
        return V;
    }
}
glm::vec3 famm::CameraSystem::Right(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { V[0][0],V[1][0],V[2][0] };
}
glm::vec3 famm::CameraSystem::Left(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { -V[0][0],-V[1][0],-V[2][0] };
}
glm::vec3 famm::CameraSystem::Up(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { V[0][1],V[1][1],V[2][1] };
}
glm::vec3 famm::CameraSystem::Down(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { -V[0][1],-V[1][1],-V[2][1] };
}
glm::vec3 famm::CameraSystem::Forward(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { -V[0][2],-V[1][2],-V[2][2] };
}
glm::vec3 famm::CameraSystem::Backward(ECSManager* ECSManager) {
    getViewMatrix(ECSManager);
    return { V[0][2],V[1][2],V[2][2] };
}