#include "RenderedSystem.hpp"

bool sortBySecond(const std::pair<int, int>& a,const std::pair<int, int>& b)
{
    return (a.second > b.second);
}

void famm::RendererSystem::drawEnities(ECSManager* myManager, std::shared_ptr<CameraSystem> myCameraSystem,std::shared_ptr<LightSystem> myLightSystem)
{
    // Collect all the lights -> Donde with myLightSystem prameter

    glm::mat4 cameraVP = myCameraSystem->getProjectionMatrix(myManager) * myCameraSystem->getViewMatrix(myManager);
    std::unordered_set<Entity>::iterator it = (myCameraSystem->entitiesSet).begin();
    glm::vec3 cameraPos = myManager->getComponentData<famm::Transform>(*it).position; //Get camera position

    std::unordered_map<Entity,glm::mat4> transformations;
   
    // Let M be an empty container containing mesh renderers and their distance from the camera.
    std::vector<std::pair<Entity, float>> transparentDistances;
    std::vector<std::pair<Entity, float>> obliqueDistances;
    //Loop on all entities: 
    for (auto const& entity : entitiesSet)
    {
        auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);
        auto& myRenderStateComponent = myManager->getComponentData<famm::RenderState>(entity);

        glm::mat4 generalTransformationMatrix = glm::identity<glm::mat4>();
        Entity parentEntity = entity;

        while (parentEntity != MAX_ENTITIES + 1)
        {
            auto& parentTransformComponent = myManager->getComponentData<famm::Transform>(parentEntity);
            generalTransformationMatrix = parentTransformComponent.to_mat4() * generalTransformationMatrix;
            parentEntity = parentTransformComponent.parent;
        }

        transformations[entity] = generalTransformationMatrix; //Store object to world only
        generalTransformationMatrix = cameraVP * generalTransformationMatrix; //Edit the value to calculate depth
            
        //  Calculate the distance from camera transform to the selected entity transform.
        //  Add it to M
        if (myRenderStateComponent.blendingEnabled)
        {
            glm::vec4 transformed_center = generalTransformationMatrix * glm::vec4(0, 0, 0, 1);
            transparentDistances.push_back(std::make_pair(entity, transformed_center.z / transformed_center.w));
        }
        else
            obliqueDistances.push_back(std::make_pair(entity, 0.0));

    }
     
    //Sort M such that :
    //    - Opaque objects are before transparent objects
    //    - Transparent objects are ordered from far to near

    std::sort(transparentDistances.begin(), transparentDistances.end(), sortBySecond);
    std::vector<std::pair<Entity, float>> M(obliqueDistances);
    //Append transparent
    M.insert(M.end(), transparentDistances.begin(), transparentDistances.end()); 


    // Loop on All M
    for (auto const& [entity,depth] : M)
    {
        auto& myRendererComponent = myManager->getComponentData<famm::MeshRenderer>(entity);
        auto& myTransformComponent = myManager->getComponentData<famm::Transform>(entity);
        auto& myRenderStateComponent = myManager->getComponentData<famm::RenderState>(entity);

        std::vector<std::pair<Texture2D*, Sampler*>>& samplers2D = myRendererComponent.material->getMaterials();
        // Setup Material:

            /// (a) Use shader program
            ShaderProgram* currentProgram = myRendererComponent.material->getShaderProgram();
            glUseProgram(*currentProgram);

            /// (b) Send transform and camera variables to shader uniforms 
            if(samplers2D.size() > 1)
            { 
                currentProgram->set(0, transformations[entity]); //Uniform object_to_world is always 0
                currentProgram->set(1, glm::inverse(transformations[entity]), true); //Uniform object_to_world_inv_transpose is always 1
                currentProgram->set(2, cameraVP); //Uniform view_projection is always 2
                currentProgram->set(3, cameraPos); //Uniform camera_position is always 3
            }
            else
            {
                currentProgram->set(0, cameraVP * transformations[entity]); //Uniform object_to_world is always 0
            }
            /// (c) Send material variables to shader uniforms
            if (samplers2D.size() > 1)
            {
                GLuint currentLocation = myRendererComponent.material->getLocation("material.albedo_tint");
                currentProgram->set(currentLocation, myRendererComponent.material->getVec3(currentLocation));

                currentLocation = myRendererComponent.material->getLocation("material.specular_tint");
                currentProgram->set(currentLocation, myRendererComponent.material->getVec3(currentLocation));

                currentLocation = myRendererComponent.material->getLocation("material.roughness_range");
                currentProgram->set(currentLocation, myRendererComponent.material->getVec2(currentLocation));

                currentLocation = myRendererComponent.material->getLocation("material.emissive_tint");
                currentProgram->set(currentLocation, myRendererComponent.material->getVec3(currentLocation));
            }

            GLuint texture_unit = 0;
            std::string materialSetter[5] = { "material.albedo_map","material.specular_map","material.ambient_occlusion_map","material.roughness_map","material.emissive_map" };
            if (samplers2D.size() > 1)
            for (auto const& [tex,samp] : samplers2D)
            {
                samp->bindSampler(texture_unit);
                tex->bindTexture(texture_unit);
                currentProgram->set(currentProgram->getUniformLocation(materialSetter[texture_unit]),(int)texture_unit);
                texture_unit++;
            }
            else
            for (auto const& [tex, samp] : samplers2D)
            {
                samp->bindSampler(texture_unit);
                tex->bindTexture(texture_unit);
                currentProgram->set(currentProgram->getUniformLocation("sampler"), (int)texture_unit);
                texture_unit++;
            }

            /// (d) Send lights to shader uniforms
            
            currentProgram->set(currentProgram->getUniformLocation("sky_light.top_color"), glm::vec3(0.0f));//(64/255.0, 77/ 255.0,128 / 255.0));
            currentProgram->set(currentProgram->getUniformLocation("sky_light.middle_color"), glm::vec3(0.0f));//(89/ 255.0, 89/ 255.0, 102/ 255.0));
            currentProgram->set(currentProgram->getUniformLocation("sky_light.bottom_color"), glm::vec3(0.0f));//(64/ 255.0,64 / 255.0,64 / 255.0));

            int light_index = 0;
            for (auto const&  light: myLightSystem->entitiesSet)
            {
                auto& myLightComponent = myManager->getComponentData<famm::Light>(light);
                auto& myLightTransformComponent = myManager->getComponentData<famm::Transform>(light);
                if (!myLightComponent.enabled) continue;
                std::string prefix = "lights[" + std::to_string(light_index) + "].";

                currentProgram->set(currentProgram->getUniformLocation(prefix + "type"), static_cast<int>(myLightComponent.type));
                currentProgram->set(currentProgram->getUniformLocation(prefix + "color"), myLightComponent.color);

                switch (myLightComponent.type) {
                case LightType::DIRECTIONAL:
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "direction"), glm::normalize(myLightTransformComponent.rotation));
                    break;
                case LightType::POINT:
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "position"), myLightTransformComponent.position);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_constant"), myLightComponent.constantAttenuation);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_linear"), myLightComponent.LinearAttenuation);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_quadratic"), myLightComponent.QuadraticAttenuation);
                    break;
                case LightType::SPOT:
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "position"), myLightTransformComponent.position);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "direction"), glm::normalize(myLightTransformComponent.rotation));
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_constant"), myLightComponent.constantAttenuation);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_linear"), myLightComponent.LinearAttenuation);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "attenuation_quadratic"), myLightComponent.QuadraticAttenuation);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "inner_angle"), myLightComponent.InnerSpotAngle);
                    currentProgram->set(currentProgram->getUniformLocation(prefix + "outer_angle"), myLightComponent.OuterSpotAngle);
                    break;
                }
                light_index++;
                if (light_index >= myLightSystem->MAX_LIGHT_COUNT) break;
            }
            
            currentProgram->set(4, light_index); //Uniform light_count is always 4

            /// (e) Use the render state to set openGL state
            if (myRenderStateComponent.blendingEnabled) glEnable(GL_BLEND);
            else glDisable(GL_BLEND);

            glDepthMask(!myRenderStateComponent.blendingEnabled || myRenderStateComponent.transparentDepthEnabled);

            if(myRenderStateComponent.depthEnabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
            glDepthFunc(myRenderStateComponent.depthFunction);

            if (myRenderStateComponent.cullingEnabled) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
            glCullFace(myRenderStateComponent.cullingFaceToCull);
            glFrontFace(myRenderStateComponent.cullingFrontFace);

            glBlendEquation(myRenderStateComponent.blendEquation);
            glBlendFunc(myRenderStateComponent.blendSourceFactor, myRenderStateComponent.blendDestFactor);
            glBlendColor(myRenderStateComponent.blendColor.r, myRenderStateComponent.blendColor.g, myRenderStateComponent.blendColor.b, myRenderStateComponent.blendColor.a);

            // Alpha to cov & test
            if (myRenderStateComponent.alphaToCoverageEnabled) glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            else glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

            if (myRenderStateComponent.alphaTestingEnabled) currentProgram->set(5, myRenderStateComponent.alphaTestingThreshold); //Uniform alpha_threshold is always 5


        // (2) Draw the entity using its attached mesh renderer component
        myRendererComponent.mesh->draw();
        

        glDepthMask(GL_TRUE);
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