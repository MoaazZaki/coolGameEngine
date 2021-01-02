#include "Game.hpp"

void famm::Game::onInitialize()
{
	// Creating components
	myManager.addComponentType<famm::MeshRenderer>();
	myManager.addComponentType<famm::Transform>();
	myManager.addComponentType<famm::Camera>();
	myManager.addComponentType<famm::CameraController>();
	myManager.addComponentType<famm::RenderState>();
	myManager.addComponentType<famm::Light>();

	// Creating systems
	auto& rendererSystem = myManager.addSystem<famm::RendererSystem>();
	mySystems.push_back(rendererSystem);
	auto& cameraSystem = myManager.addSystem<famm::CameraSystem>();
	mySystems.push_back(cameraSystem);
	auto& cameraControllerSystem = myManager.addSystem<famm::CameraControllerSystem>();
	mySystems.push_back(cameraControllerSystem);
	auto& lightSystem = myManager.addSystem<famm::LightSystem>();
	mySystems.push_back(lightSystem);

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

	Entity worldEntity;
	Entity object;
	Entity camera;
	Entity cameraController;

	//Creating Default render state
	RenderState defaultState;
	RenderState transparentState;
	transparentState.blendingEnabled = true;
	//World Entity (root of scene)
	worldEntity = myManager.createEntity();
	myManager.addComponentData<Transform>(worldEntity, famm::Transform({ 0,0,0 }, { 0,0,0 }, { 1,1,1 },MAX_ENTITIES+1));
	//world.push_back(worldEntity);

	//Land Entity
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("land"),myStore->getMaterialPointer("land"), {0.901, 0.670, 0.419,0} }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 30,3,20 }, { 0,0,0 }, { 1000,1000,1000 }, worldEntity));
	myManager.addComponentData<RenderState>(object, defaultState);
	world.push_back(object);

	//Wolf Entity
	//Entity wolfParent = object;			//making Tree 2 the parent of the wolf
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("sphere"),myStore->getMaterialPointer("Suzanne"),{0.4, 0.352, 0.301,0} }));
	myManager.addComponentData<Transform>(object, famm::Transform({35.6,9.7,4 }, { 0,-0.9,0 }, { 10,10,10 }, worldEntity));
	myManager.addComponentData<RenderState>(object, transparentState);
	world.push_back(object);


	////////////////////////////////
	//Wolf Entity
	//Entity wolfParent = object;			//making Tree 2 the parent of the wolf
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("Suzanne"),myStore->getMaterialPointer("Suzanne2"),{0.4, 0.352, 0.301,0} }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 92.4,9.6,-8.8 }, { 0,-0.9,0 }, { 10,10,10 }, worldEntity));
	myManager.addComponentData<RenderState>(object, defaultState);
	world.push_back(object);

	////////////////////////////////
	//Wolf Entity
	//Entity wolfParent = object;			//making Tree 2 the parent of the wolf
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("Suzanne"),myStore->getMaterialPointer("Suzanne"),{0.4, 0.352, 0.301,0} }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 74.2,11.2,1 }, { 0,-0.9,0 }, { 10,10,10 }, worldEntity));
	myManager.addComponentData<RenderState>(object, transparentState);
	world.push_back(object);

	//Camera Entity
	camera = myManager.createEntity();
	myManager.addComponentData<Camera>(camera, famm::Camera(
		{
			1,
			{0,0,0},
			0.01f,
			1000.0f,
			16.0/9.0,
			glm::radians(90.0f),
			2.0f,
			glm::radians(90.0f)
		}));
	myManager.addComponentData<Transform>(camera, famm::Transform({ 10, 10, 10 }, { -10, -10, -10 }));


	//Camera controller Entity 
	cameraController = myManager.createEntity();
	myManager.addComponentData<CameraController>(cameraController, famm::CameraController({ camera,{3.0f, 3.0f, 3.0f},0.01f,0.01f,glm::pi<float>() / 10,5.0f,false}));

	////Light Entity
	Entity defaultLight = myManager.createEntity();
	myManager.addComponentData<Light>(defaultLight, famm::Light({ true,famm::LightType::DIRECTIONAL,{1.0,0.7,0.2},0,0,0,0,0 }));
	myManager.addComponentData<Transform>(defaultLight, famm::Transform({ 0, 0, 0 }, { -1.5, -15, -2.6 }));
	lightArray.push_back(defaultLight); // TODO: REMOVE THISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	glClearColor(0, 0, 0, 0);
}


void famm::Game::onDraw(double deltaTime) {
	std::shared_ptr<RendererSystem> RS = std::static_pointer_cast<RendererSystem>(mySystems[0]);
	std::shared_ptr <CameraSystem> CS = std::static_pointer_cast<CameraSystem>(mySystems[1]);
	std::shared_ptr<CameraControllerSystem> CCS = std::static_pointer_cast<CameraControllerSystem>(mySystems[2]);
	std::shared_ptr<LightSystem> LS = std::static_pointer_cast<LightSystem>(mySystems[3]);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!isPaused)
	{
		CCS->moveCamera(&myManager, deviceManager, deltaTime, CS);
		RS->drawEnities(&myManager, CS,LS);
	}
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused)) onPause();
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::DEV, famm::PressModes::JUST_PRESSED) && !isPaused)) developementMode = !developementMode;
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

		for (int i = 0; i < world.size(); i++)
		{
			std::string entityString = std::to_string(world[i]);

			auto& myTransformComponent = myManager.getComponentData<famm::Transform>(world[i]);
			auto& myRemderStateComponent = myManager.getComponentData<famm::RenderState>(world[i]);

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


	std::vector<std::string> models = { "Suzanne","cube","land" };
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

	famm::ReorderableList(std::begin(world), std::end(world),
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
			myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer(models[item_current_idx].c_str()),myStore->getMaterialPointer(models[item_current_idx].c_str()) }));
			myManager.addComponentData<Transform>(object, famm::Transform(translation, rotation, scale));
			myManager.addComponentData<RenderState>(object, defaultState);
			world.insert(std::begin(world) + index, object);
		},
			[&](size_t index) {
			myManager.destroyEntity(world[index]);
			world.erase(std::begin(world) + index);
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