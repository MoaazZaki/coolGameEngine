
#include "CameraSystem.hpp"


void famm::CameraSystem::setType(bool projectionType,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
       /* auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.projectionType = projectionType;*/
    }
}

void famm::CameraSystem::setOrthographicSize(float orthographic_height,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.orthographic_height = orthographic_height;
    }
}

void famm::CameraSystem::setVerticalFieldOfView(float field_of_view_y,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.field_of_view_y = field_of_view_y;
    }
}

void famm::CameraSystem::setAspectRatio(float aspect_ratio,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.aspect_ratio = aspect_ratio;
    }
}

void famm::CameraSystem::setNearPlane(float near,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.near = near;
    }
}

void famm::CameraSystem::setFarPlane(float far,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.far = far;
    }
}

void famm::CameraSystem::setEyePosition(glm::vec3 eye,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.eye = eye;
    }
}

void famm::CameraSystem::setDirection(glm::vec3 direction,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.direction = direction;
    }
}

void famm::CameraSystem::setTarget(glm::vec3 target,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.target = target;
    }
}

void famm::CameraSystem::setUp(glm::vec3 up,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.up = up;
    }
}

void famm::CameraSystem::setVericalFieldOFViewAngle(float vertical_field_of_view_angle,  ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        camera.vertical_field_of_view_angle = vertical_field_of_view_angle;
    }
}

bool famm::CameraSystem::getType( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.projectionType;
    }
}

float famm::CameraSystem::getOrthographicSize( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.orthographic_height;
    }
}

float famm::CameraSystem::getVerticalFieldOfView( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.field_of_view_y;
    }
}

float famm::CameraSystem::getAspectRatio( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.aspect_ratio;
    }
}

float famm::CameraSystem::getNearPlane( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.near;
    }
}

float famm::CameraSystem::getFarPlane( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.far;
    }
}

glm::vec3 famm::CameraSystem::getEyePosition( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.eye;
    }
}

glm::vec3 famm::CameraSystem::getDirection( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.direction;
    }
}

glm::vec3 famm::CameraSystem::getTarget( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.target;
    }
}

glm::vec3 famm::CameraSystem::getUp( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.up;
    }
}

float famm::CameraSystem::getVericalFieldOFViewAngle( ECSManager* ECSmanager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        return camera.vertical_field_of_view_angle;
    }
}

glm::mat4 famm::CameraSystem::getProjectionMatrix( ECSManager* ECSmanager) {

    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
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

glm::mat4 famm::CameraSystem::getViewMatrix( ECSManager* ECSmanager) {

    for (auto const& entity : entitiesSet)
    {
        auto& camera = ECSmanager->getComponentData<Camera>(entity);
        V = glm::lookAt(camera.eye, camera.eye + camera.direction, camera.up);
        return V;
    }
}
glm::vec3 famm::CameraSystem::Right( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { V[0][0],V[1][0],V[2][0] };
}
glm::vec3 famm::CameraSystem::Left( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { -V[0][0],-V[1][0],-V[2][0] };
}
glm::vec3 famm::CameraSystem::Up( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { V[0][1],V[1][1],V[2][1] };
}
glm::vec3 famm::CameraSystem::Down( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { -V[0][1],-V[1][1],-V[2][1] };
}
glm::vec3 famm::CameraSystem::Forward( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { -V[0][2],-V[1][2],-V[2][2] };
}
glm::vec3 famm::CameraSystem::Backward( ECSManager* ECSmanager) {
    getViewMatrix(ECSmanager);
    return { V[0][2],V[1][2],V[2][2] };
}