#include "RenderedSystem.hpp"

void famm::RendererSystem::drawEnities(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);
        auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);

        ShaderProgram* currentProgram = myRendererComponent.material->getShaderProgram();
        glUseProgram(*currentProgram);
        currentProgram->set(1, glm::vec4(1, 1, 1, 1));
        currentProgram->set(0, myCameraSystem->getProjectionMatrix(myManager) * myCameraSystem->getViewMatrix(myManager) * myTransformComponent.to_mat4()); //Uniform position is always 0

        myRendererComponent.mesh->draw();

    }
}

void famm::RendererSystem::updateEntites(ECSManager* myManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);
        //TODO: UPDATE UNIFORMS EXCEPT POSITION
        
    }
}

void famm::RendererSystem::cleanEntities(ECSManager* myManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);

        myRendererComponent.mesh->destroy();
    }
}