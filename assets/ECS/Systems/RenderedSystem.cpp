#include "RenderedSystem.hpp"

void famm::RendererSystem::drawEnities(ECSManager* myManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = ECSmanager->getComponentData<famm::MeshRenderer>(entity);

        glUseProgram(*myRendererComponent.material->getShaderProgram());
        myRendererComponent.mesh.draw();
    }
}

void famm::RendererSystem::updateEntites(ECSManager* myManager)
{
    for (auto const& entity : entitiesSet)
    {
        auto& myRendererComponent = ECSmanager->getComponentData<famm::MeshRenderer>(entity);
        myRendererComponent.material->onUpdateShaderScalar();
        myRendererComponent.material->onUpdateShaderVector2();
        myRendererComponent.material->onUpdateShaderVector3();
    }
}