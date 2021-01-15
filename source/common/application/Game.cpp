#include "Game.hpp"
////////////// JSON UTILS ///////////////////
// JSON Types
struct meshRendererJSON {
	std::string mesh;
	std::string material;
	glm::vec4 tint;
};
struct componentJSON {
	std::string type;
	// Possible component container
	famm::Transform* transform;
	meshRendererJSON meshRenderer;
	famm::Camera* camera;
	famm::CameraController* cameraController;
	famm::RenderState* renderState;
	famm::Light* light;
	famm::Interaction* interaction;
	famm::Collider* collider;
};

// JSON Functions

void from_json(const nlohmann::json& j, componentJSON& c)
{
	j.at("type").get_to(c.type);
	if (c.type == "transform")
	{
		c.transform = new famm::Transform;
		c.transform->position = j.value<glm::vec3>("position", { 0.0f,0.0f,0.0f });
		c.transform->rotation = j.value<glm::vec3>("rotation", { 0.0f,0.0f,0.0f });
		c.transform->scale = j.value<glm::vec3>("scale", { 1.0f,1.0f,1.0f });
	}
	else if (c.type == "meshRenderer")
	{
		j.at("mesh").get_to(c.meshRenderer.mesh);
		j.at("material").get_to(c.meshRenderer.material);
		c.meshRenderer.tint = j.value<glm::vec4>("tint", { 1.0f,1.0f,1.0f,1.0f });
	}
	else if (c.type == "collider")
	{
		c.collider = new famm::Collider;
		c.collider->enabled = (bool)j.value<int>("enabled", 1);
	}
	else if (c.type == "renderState")
	{
		c.renderState = new famm::RenderState;
		// Enables
		c.renderState->alphaTestingEnabled = (bool)j.value<int>("alphaTestingEnabled", 1);
		c.renderState->alphaToCoverageEnabled = (bool)j.value<int>("alphaToCoverageEnabled", 0);
		c.renderState->depthEnabled = (bool)j.value<int>("depthEnabled", 1);
		c.renderState->transparentDepthEnabled = (bool)j.value<int>("transparentDepthEnabled", 1);
		c.renderState->blendingEnabled = (bool)j.value<int>("blendingEnabled",0);
		c.renderState->cullingEnabled = (bool)j.value<int>("cullingEnabled", 1);

		// Culling
		std::string mode = j.value<std::string>("cullingFaceToCull", "GL_BACK");
		c.renderState->cullingFaceToCull = (mode == "GL_BACK") ? GL_BACK : ((mode == "GL_FRONT") ? GL_FRONT : (mode == "GL_FRONT_AND_BACK") ? GL_FRONT_AND_BACK : GL_BACK);
		mode = j.value<std::string>("cullingFrontFace", "GL_CCW");
		c.renderState->cullingFrontFace = (mode == "GL_CCW") ? GL_CCW : ((mode == "GL_CW") ? GL_CW : GL_CCW);

		// Blending 
		mode = j.value<std::string>("blendEquation", "GL_FUNC_ADD");
		c.renderState->blendEquation = (mode == "GL_FUNC_ADD") ? GL_FUNC_ADD : ((mode == "GL_FUNC_SUBTRACT") ? GL_FUNC_SUBTRACT : ((mode == "GL_FUNC_REVERSE_SUBTRACT") ? GL_FUNC_REVERSE_SUBTRACT : ((mode == "GL_MIN") ? GL_MIN : ((mode == "GL_MAX") ? GL_MAX : GL_FUNC_ADD))));
		mode = j.value<std::string>("blendSourceFactor", "GL_SRC_ALPHA");
		c.renderState->blendSourceFactor = (mode == "GL_SRC_ALPHA") ? GL_SRC_ALPHA : ((mode == "GL_ZERO") ? GL_ZERO : ((mode == "GL_ONE") ? GL_ONE : ((mode == "GL_SRC_COLOR") ? GL_SRC_COLOR : ((mode == "GL_ONE_MINUS_SRC_COLOR") ? GL_ONE_MINUS_SRC_COLOR : ((mode == "GL_DST_COLOR") ? GL_DST_COLOR : ((mode == "GL_ONE_MINUS_DST_COLOR") ? GL_ONE_MINUS_DST_COLOR : ((mode == "GL_ONE_MINUS_SRC_ALPHA") ? GL_ONE_MINUS_SRC_ALPHA : ((mode == "GL_DST_ALPHA") ? GL_DST_ALPHA : ((mode == "GL_ONE_MINUS_DST_ALPHA") ? GL_ONE_MINUS_DST_ALPHA : ((mode == "GL_CONSTANT_COLOR") ? GL_CONSTANT_COLOR : ((mode == "GL_ONE_MINUS_CONSTANT_COLOR") ? GL_ONE_MINUS_CONSTANT_COLOR : ((mode == "GL_CONSTANT_ALPHA") ? GL_CONSTANT_ALPHA : ((mode == "GL_ONE_MINUS_CONSTANT_ALPHA") ? GL_ONE_MINUS_CONSTANT_ALPHA : GL_SRC_ALPHA)))))))))))));
		mode = j.value<std::string>("blendDestFactor", "GL_ONE_MINUS_SRC_ALPHA");
		c.renderState->blendDestFactor = (mode == "GL_SRC_ALPHA") ? GL_SRC_ALPHA : ((mode == "GL_ZERO") ? GL_ZERO : ((mode == "GL_ONE") ? GL_ONE : ((mode == "GL_SRC_COLOR") ? GL_SRC_COLOR : ((mode == "GL_ONE_MINUS_SRC_COLOR") ? GL_ONE_MINUS_SRC_COLOR : ((mode == "GL_DST_COLOR") ? GL_DST_COLOR : ((mode == "GL_ONE_MINUS_DST_COLOR") ? GL_ONE_MINUS_DST_COLOR : ((mode == "GL_ONE_MINUS_SRC_ALPHA") ? GL_ONE_MINUS_SRC_ALPHA : ((mode == "GL_DST_ALPHA") ? GL_DST_ALPHA : ((mode == "GL_ONE_MINUS_DST_ALPHA") ? GL_ONE_MINUS_DST_ALPHA : ((mode == "GL_CONSTANT_COLOR") ? GL_CONSTANT_COLOR : ((mode == "GL_ONE_MINUS_CONSTANT_COLOR") ? GL_ONE_MINUS_CONSTANT_COLOR : ((mode == "GL_CONSTANT_ALPHA") ? GL_CONSTANT_ALPHA : ((mode == "GL_ONE_MINUS_CONSTANT_ALPHA") ? GL_ONE_MINUS_CONSTANT_ALPHA : GL_ONE_MINUS_SRC_ALPHA)))))))))))));
		c.renderState->blendColor = j.value<glm::vec4>("blendColor", { 1.0f,1.0f,1.0f,1.0f });

		// Depth testing
		mode =j.value<std::string>("depthFunction", "GL_LEQUAL");
		c.renderState->depthFunction = (mode == "GL_LEQUAL") ? GL_LEQUAL : ((mode == "GL_ALWAYS") ? GL_ALWAYS : ((mode == "GL_NEVER") ? GL_NEVER : ((mode == "GL_EQUAL") ? GL_EQUAL : ((mode == "GL_NOTEQUAL") ? GL_NOTEQUAL : ((mode == "GL_LESS") ? GL_LESS : ((mode == "GL_GREATER") ? GL_GREATER : ((mode == "GL_GEQUAL") ? GL_GEQUAL : GL_LEQUAL)))))));

		// Alpha testing
		c.renderState->alphaTestingThreshold = j.value<float>("alphaTestingThreshold", 0.0);
	}
	else if (c.type == "camera")
	{
		c.camera = new famm::Camera;
		c.camera->enabled = (bool)j.value<int>("enabled", 1);
		c.camera->mode = (bool)j.value<int>("mode", 0);
		c.camera->projectionType = (bool)j.value<int>("projectionType", 1);
		c.camera->target = j.value<glm::vec3>("target", { 0,0,0 });
		c.camera->near = j.value<float>("near", 0.01f);
		c.camera->far = j.value<float>("far", 500.0f);
		c.camera->aspect_ratio = j.value<float>("aspect_ratio", 16.0/9.0);
		c.camera->vertical_field_of_view_angle = j.value<float>("vertical_field_of_view_angle", glm::radians(90.0f));
		c.camera->field_of_view_y = j.value<float>("field_of_view_y", glm::radians(90.0f));
		c.camera->orthographic_height = j.value<float>("field_of_view_y", 2.0f);
		c.camera->yaw = j.value<float>("yaw", 0.0f);
		c.camera->pitch = j.value<float>("pitch", 0.0f);
	}
	else if (c.type == "cameraController")
	{
		c.cameraController = new famm::CameraController;
		c.cameraController->position_sensitivity = j.value<glm::vec3>("position_sensitivity", { 30.0f, 30.0f, 30.0f });
		c.cameraController->yaw_sensitivity = j.value<float>("yaw_sensitivity", 0.01f);
		c.cameraController->pitch_sensitivity = j.value<float>("pitch_sensitivity", 0.01f);
		c.cameraController->fov_sensitivity = j.value<float>("fov_sensitivity", glm::pi<float>());
		c.cameraController->speedup_factor = j.value<float>("speedup_factor", 1.5f);
		c.cameraController->mouse_locked = (bool)j.value<int>("mouse_locked", 0);
	}
	else if (c.type == "light")
	{
		c.light = new famm::Light;
		c.light->enabled = (bool)j.value<int>("enabled", 1);
		c.light->type = (famm::LightType)j.value<int>("lightType", 0);
		c.light->color = j.value<glm::vec3>("color", {0.0f,0.0f,0.0f});
		c.light->constantAttenuation = j.value<float>("constantAtt", 0.0f);
		c.light->LinearAttenuation = j.value<float>("linearAtt", 0.0f);
		c.light->QuadraticAttenuation = j.value<float>("quadraticAtt", 0.0f);
	}
	else if (c.type == "interaction")
	{
		c.interaction = new famm::Interaction;
		c.interaction->enabled = (bool)j.value<int>("enabled", 0);
		c.interaction->distanceOfInertaction = j.value<float>("distanceOfInteraction", 0.01);
		c.interaction->buttonOfInteraction = (famm::ControlsActions)j.value<int>("buttonOfInteraction", 0);
		c.interaction->on = j.value<GLbyte>("on", 1);
		c.interaction->parent = j.value<int>("parent", 0);
		c.interaction->action = j.value<GLbyte>("action", 0);
		c.interaction->componentType = j.value<GLbyte>("componentType", 0);
	}
}

void famm::Game::extractWorld(const nlohmann::json& j, famm::Entity parent,famm::Entity interactionParent, Store* myStore, ECSManager* myManager)
{
	Entity object;
	for (auto& entity : j["entities"])
	{
		object = myManager->createEntity();
		for (auto& compoent : entity["components"])
		{
			componentJSON c = compoent;
			if (c.type == "transform")
			{
				c.transform->parent = parent;
				myManager->addComponentData<Transform>(object,*c.transform);
				if (compoent.contains("children")) extractWorld(compoent["children"], object,0, myStore, myManager);
			}
			else if (c.type == "meshRenderer")
			{
				myManager->addComponentData<MeshRenderer>(object, MeshRenderer({ (bool)compoent.value<int>("enabled", 1),myStore->getMeshPointer(c.meshRenderer.mesh),myStore->getMaterialPointer(c.meshRenderer.material), c.meshRenderer.tint }));
			}
			else if (c.type == "renderState")
			{
				myManager->addComponentData<RenderState>(object, *c.renderState);
				worldArray.push_back(object);
			}
			else if (c.type == "collider")
			{
				MeshRenderer currentMesh;
				if (c.meshRenderer.mesh != "cuboid" && c.meshRenderer.mesh != "plane" && c.meshRenderer.mesh != "sphere")
				{
					currentMesh = myManager->getComponentData<MeshRenderer>(object);
					c.collider->AABBcorners[0] = currentMesh.mesh->mingetMinBound();
					c.collider->AABBcorners[1] = currentMesh.mesh->mingetMaxBound();
					myManager->addComponentData<Collider>(object, *c.collider);
				}
			}
			else if (c.type == "camera")
			{
				myManager->addComponentData<Camera>(object, *c.camera);
				if (compoent.contains("controller")) extractWorld(compoent["controller"], object,0, myStore, myManager);
			}
			else if (c.type == "cameraController")
			{
				c.cameraController->controlledCamera = parent;
				myManager->addComponentData<CameraController>(object, *c.cameraController);
			}
			else if (c.type == "light")
			{
				myManager->addComponentData<Light>(object, *c.light);
				lightArray.push_back(object);
			}
			else if (c.type == "interaction")
			{
				if (interactionParent != 0) c.interaction->parent = interactionParent;
				myManager->addComponentData<Interaction>(object, *c.interaction);
				if (compoent.contains("with"))
				{
					if ((bool)compoent.value<int>("attachTransformation", 0))
						extractWorld(compoent["with"], object, object, myStore, myManager);
					else
						extractWorld(compoent["with"], parent, object, myStore, myManager);
				}
			}
		}
	}
}


void famm::Game::onInitialize()
{
	// Creating components
	myManager.addComponentType<famm::MeshRenderer>();
	myManager.addComponentType<famm::Transform>();
	myManager.addComponentType<famm::Camera>();
	myManager.addComponentType<famm::CameraController>();
	myManager.addComponentType<famm::RenderState>();
	myManager.addComponentType<famm::Light>();
	myManager.addComponentType<famm::Interaction>();
	myManager.addComponentType<famm::Collider>();
	myManager.addComponentType<famm::Progress>();

	// Creating systems
	auto& rendererSystem = myManager.addSystem<famm::RendererSystem>();
	mySystems.push_back(rendererSystem);
	auto& cameraSystem = myManager.addSystem<famm::CameraSystem>();
	mySystems.push_back(cameraSystem);
	auto& cameraControllerSystem = myManager.addSystem<famm::CameraControllerSystem>();
	mySystems.push_back(cameraControllerSystem);
	auto& lightSystem = myManager.addSystem<famm::LightSystem>();
	mySystems.push_back(lightSystem);
	auto& interactionSystem = myManager.addSystem<famm::InteractionSystem>();
	mySystems.push_back(interactionSystem);
	auto& colliderSystem = myManager.addSystem<famm::ColliderSystem>();
	mySystems.push_back(colliderSystem);
	auto& progressSystem = myManager.addSystem<famm::ProgressSystem>();
	mySystems.push_back(progressSystem);

	// Setting signatures
	famm::Signature signature;
	signature.set(myManager.getComponentType<famm::MeshRenderer>());
	signature.set(myManager.getComponentType<famm::Transform>());
	signature.set(myManager.getComponentType<famm::RenderState>());
	myManager.setSystemSignature<RendererSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Camera>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<CameraSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::CameraController>());
	myManager.setSystemSignature<CameraControllerSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Light>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<LightSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Interaction>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<InteractionSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Collider>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<ColliderSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Progress>());
	myManager.setSystemSignature<ProgressSystem>(signature);

	Entity worldEntity;
	Entity object;
	Entity camera;
	Entity cameraController;

	std::ifstream file_in("assets/data/world.json"); 
	nlohmann::json world;
	file_in >> world;
	file_in.close();

	extractWorld(world, MAX_ENTITIES + 1,0, myStore, &myManager);
	progressSystem->assignProgress();
	
	glClearColor(7/255.0,12/255.0, 41/ 255.0, 1);
}

void famm::Game::onDraw(double deltaTime) {
	std::shared_ptr<RendererSystem> RS = std::static_pointer_cast<RendererSystem>(mySystems[0]);
	std::shared_ptr <CameraSystem> CS = std::static_pointer_cast<CameraSystem>(mySystems[1]);
	std::shared_ptr<CameraControllerSystem> CCS = std::static_pointer_cast<CameraControllerSystem>(mySystems[2]);
	std::shared_ptr<LightSystem> LS = std::static_pointer_cast<LightSystem>(mySystems[3]);
	std::shared_ptr<InteractionSystem> IS = std::static_pointer_cast<InteractionSystem>(mySystems[4]);
	std::shared_ptr<ColliderSystem> CDS = std::static_pointer_cast<ColliderSystem>(mySystems[5]);
	std::shared_ptr<ProgressSystem> PS = std::static_pointer_cast<ProgressSystem>(mySystems[6]);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!isPaused)
	{
		CCS->moveCamera(&myManager, deviceManager, deltaTime, CS);
		RS->drawEnities(&myManager, CS,LS);
		IS->updateInteractions(&myManager, deviceManager,CS, PS);
		CDS->updateColliders(&myManager, CS);
	}
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused))
	{
		deviceManager->getMouse().unlockMouse(deviceManager->getWindow());
		onPause();
	}
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::DEV, famm::PressModes::JUST_PRESSED) && !isPaused))
	{
		developementMode = !developementMode;
	}
}

void famm::Game::lightGui(ImGuiIO* io)
{
	static const std::unordered_map<LightType, const char*> light_type_names = {
		{LightType::DIRECTIONAL, "Directional"},
		{LightType::POINT, "Point"},
		{LightType::SPOT, "Spot"}
	};

	ImGui::Begin("Lights");
	
	famm::ReorderableList(lightArray.begin(), lightArray.end(),
						[&](size_t index, Entity& entity) {
							auto& light = myManager.getComponentData<famm::Light>(entity);
							auto& transform = myManager.getComponentData<famm::Transform>(entity);

							ImGui::Checkbox("Enabled", &light.enabled);
							if (ImGui::BeginCombo("Type", light_type_names.at(light.type))) {
								for (auto& [type, name] : light_type_names) {
									bool selected = light.type == type;
									if (ImGui::Selectable(name, selected))
										light.type = type;
									if (selected) ImGui::SetItemDefaultFocus();
								}
								ImGui::EndCombo();
							}

							ImGui::ColorEdit3("Color", glm::value_ptr(light.color), ImGuiColorEditFlags_HDR);

							switch (light.type) {
							case LightType::DIRECTIONAL:
								
								ImGui::DragFloat3("Direction", glm::value_ptr(transform.rotation), 0.1f);
								break;
							case LightType::POINT:
								ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
								ImGui::Separator();
								ImGui::DragFloat("Constant Attenuation", &light.constantAttenuation, 0.1f);
								ImGui::DragFloat("Linear Attenuation", &light.LinearAttenuation, 0.1f);
								ImGui::DragFloat("Quadratic Attenuation", &light.QuadraticAttenuation, 0.1f);
								break;
							case LightType::SPOT:
								ImGui::DragFloat3("Direction", glm::value_ptr(transform.rotation), 0.1f);
								ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
								ImGui::Separator();
								ImGui::DragFloat("Constant Attenuation", &light.constantAttenuation, 0.1f);
								ImGui::DragFloat("Linear Attenuation", &light.LinearAttenuation, 0.1f);
								ImGui::DragFloat("Quadratic Attenuation", &light.QuadraticAttenuation, 0.1f);
								ImGui::Separator();
								ImGui::DragFloat("Inner Spot Angle", &light.InnerSpotAngle, 0.1f, 0.0f, glm::two_pi<float>());
								ImGui::DragFloat("Outer Spot Angle", &light.OuterSpotAngle, 0.1f, 0.0f, glm::two_pi<float>());
								break;
							}
		},
		[&](size_t index) {
			Entity object;
			object = myManager.createEntity();
			myManager.addComponentData<Light>(object, famm::Light({ true,famm::LightType::DIRECTIONAL,{0,0,0},0,0,0,0,0 }));
			myManager.addComponentData<Transform>(object, famm::Transform({0,0,0}, {0,0,0}));
			lightArray.insert(lightArray.begin() + index, object);
		},
		[&](size_t index) {
			myManager.destroyEntity(lightArray[index]);
			lightArray.erase(std::begin(lightArray) + index);
		});

	ImGui::End();

}

void famm::Game::transformationGui(ImGuiIO* io)
{
	io->WantCaptureMouse = true;

	if (ImGui::TreeNode("Transformation")) {
		/*if (node->mesh.has_value()) {
			famm::PairIteratorCombo("Mesh", node->mesh.value(), meshes.begin(), meshes.end());
			ImGui::ColorEdit4("Tint", glm::value_ptr(node->tint));
		}*/
		//char num_char[5 + sizeof(char)];
		static std::string translateString = "Translation##";
		static std::string rotateString = "Rotation##";
		static std::string scaleString = "Scale##";

		static std::string BEString = "Enable Blending##";
		static std::string BEQString = "Equation##";
		static std::string BSFString = "Source Function##";
		static std::string BDFString = "Destination Function##";
		static std::string BCCString = "Blend Constant Color##";

		static std::string ATEString = "Enable Alpha Testing##";
		static std::string ATHString = "Alpha Threshold##";

		static std::string ATCErotateString = "Enable Alpha To Coverage##";

		static std::string DTEscaleString = "Enable Depth Testing##";
		static std::string DTFscaleString = "Comparison Function##";
		static std::string DWEscaleString = "Enable Transparent Depth Write##";

		static std::string FCEString = "Enable Face Culling##";
		static std::string FTCString = "Face To Cull##";
		static std::string FFCString = "Front Face##";

		for (int i = 0; i < worldArray.size(); i++)
		{
			std::string entityString = std::to_string(worldArray[i]);

			auto& myTransformComponent = myManager.getComponentData<famm::Transform>(worldArray[i]);
			auto& myRemderStateComponent = myManager.getComponentData<famm::RenderState>(worldArray[i]);

			ImGui::Text(entityString.c_str());

			ImGui::DragFloat3((translateString + entityString).c_str(), glm::value_ptr(myTransformComponent.position), 0.1f);
			ImGui::DragFloat3((rotateString + entityString).c_str(), glm::value_ptr(myTransformComponent.rotation), 0.01f);
			ImGui::DragFloat3((scaleString + entityString).c_str(), glm::value_ptr(myTransformComponent.scale), 0.1f);

			ImGui::Checkbox((BEString + entityString).c_str(), &myRemderStateComponent.blendingEnabled);
			famm::OptionMapCombo((BEQString + entityString).c_str(), myRemderStateComponent.blendEquation, famm::gl_enum_options::blend_equations);
			famm::OptionMapCombo((BSFString + entityString).c_str(), myRemderStateComponent.blendSourceFactor, famm::gl_enum_options::blend_functions);
			famm::OptionMapCombo((BDFString + entityString).c_str(), myRemderStateComponent.blendDestFactor, famm::gl_enum_options::blend_functions);
			ImGui::ColorEdit4((BCCString + entityString).c_str(), glm::value_ptr(myRemderStateComponent.blendColor), ImGuiColorEditFlags_HDR);



			ImGui::Checkbox((ATEString + entityString).c_str(), &myRemderStateComponent.alphaTestingEnabled);
			ImGui::DragFloat((ATHString + entityString).c_str(), &myRemderStateComponent.alphaTestingThreshold, 0.01f, 0.0f, 1.0f);



			ImGui::Checkbox((ATCErotateString + entityString).c_str(), &myRemderStateComponent.alphaToCoverageEnabled);



			ImGui::Checkbox((DTEscaleString + entityString).c_str(), &myRemderStateComponent.depthEnabled);
			famm::OptionMapCombo((DTFscaleString + entityString).c_str(), myRemderStateComponent.depthFunction, famm::gl_enum_options::comparison_functions);
			ImGui::Checkbox((DWEscaleString + entityString).c_str(), &myRemderStateComponent.transparentDepthEnabled);


			ImGui::Checkbox((FCEString + entityString).c_str(), &myRemderStateComponent.cullingEnabled);
			famm::OptionMapCombo((FTCString + entityString).c_str(), myRemderStateComponent.cullingFaceToCull, famm::gl_enum_options::facets);
			famm::OptionMapCombo((FFCString + entityString).c_str(), myRemderStateComponent.cullingFrontFace, famm::gl_enum_options::face_windings);

			ImGui::Separator();
		}

		ImGui::TreePop();
	}
}

void famm::Game::newModelGui(ImGuiIO* io)
{
	ImGui::Begin("New Model");

	int max_element = 0;
	float speed = 0;


	std::vector<std::string> models = { "plane","cuboid" };
	std::vector<std::string> materials = { "floor","metal" };
	static int item_current_idx = 0;
	if (ImGui::BeginCombo("Models", models[item_current_idx].c_str()))
	{
		for (int n = 0; n < models.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(models[n].c_str(), is_selected))
				item_current_idx = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}

	static glm::vec3 translation = { 0,0,0 }, rotation = { 0,0,0 }, scale = { 1,1,1 };
	ImGui::DragFloat3("Translation", glm::value_ptr(translation), 0.1f);
	ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.01f);
	ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);

	famm::ReorderableList(std::begin(worldArray), std::end(worldArray),
		[&](size_t index, Entity& element) {
			std::string str_id = std::to_string(index);
			int element_i32 = element;
			ImGui::Text(str_id.c_str());
			element = element_i32;
		},
		[&](size_t index) {
			Entity object;
			RenderState defaultState;
			object = myManager.createEntity();
			myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ true,myStore->getMeshPointer(models[item_current_idx].c_str()),myStore->getMaterialPointer(materials[item_current_idx].c_str()) }));
			myManager.addComponentData<Transform>(object, famm::Transform(translation, rotation, scale));
			myManager.addComponentData<RenderState>(object, defaultState);
			worldArray.insert(std::begin(worldArray) + index, object);
		},
			[&](size_t index) {
			myManager.destroyEntity(worldArray[index]);
			worldArray.erase(std::begin(worldArray) + index);
		});
	ImGui::End();
}

void famm::Game::onImmediateGui(ImGuiIO* io)
{
	if (developementMode)
	{
		transformationGui(io);
		newModelGui(io);
		lightGui(io);
	}
	else
	{
		io->WantCaptureMouse = false;
	}
}


void famm::Game::onDestroy() {
	std::shared_ptr<RendererSystem> RS = std::static_pointer_cast<RendererSystem>(mySystems[0]);
	RS->cleanEntities(&myManager);
}