#include "RenderedSystem.hpp"

void famm::RendererSystem::drawEnities(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);
        auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);
       // auto& myParentTransformComponent = myManager->getComponentData<famm::Transform>(myTransformComponent.parent);

        glm::mat4 generalTransformationMatrix = glm::identity<glm::mat4>();
        Entity parentEntity = entity;
        
        while (parentEntity != MAX_ENTITIES+1)
        {
            auto& parentTransformComponent = myManager->getComponentData<famm::Transform>(parentEntity);
            generalTransformationMatrix = parentTransformComponent.to_mat4() * generalTransformationMatrix;
            parentEntity = parentTransformComponent.parent;
        }

        ShaderProgram* currentProgram = myRendererComponent.material->getShaderProgram();
        glUseProgram(*currentProgram);
        currentProgram->set(1, myRendererComponent.tint);
        currentProgram->set(0, myCameraSystem->getProjectionMatrix(myManager) * myCameraSystem->getViewMatrix(myManager) * generalTransformationMatrix); //Uniform position is always 0
        
        myRendererComponent.mesh->draw();
        
    }
}

void famm::RendererSystem::updateEntites(ECSManager* myManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);
        //TODO: UPDATE UNIFORMS EXCEPT POSITION
        //      THIS WILL BE DONE IN THE FUTURE DEPENDING ON THE NEEDS
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