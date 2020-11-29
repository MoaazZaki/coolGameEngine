#include "Game.hpp"

void famm::Game::onInitialize()
{
	// Creating components
	myManager.addComponentType<famm::MeshRenderer>();
	myManager.addComponentType<famm::Transform>();
	myManager.addComponentType<famm::Camera>();
	myManager.addComponentType<famm::CameraController>();

	// Creating systems
	auto rendererSystem = myManager.addSystem<famm::RendererSystem>();
	mySystems.push_back(rendererSystem);
	auto cameraSystem = myManager.addSystem<famm::CameraSystem>();
	mySystems.push_back(cameraSystem);
	auto cameraControllerSystem = myManager.addSystem<famm::CameraControllerSystem>();
	mySystems.push_back(cameraControllerSystem);
	
	// Setting signatures
	famm::Signature signature;
	signature.set(myManager.getComponentType<famm::MeshRenderer>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<RendererSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Camera>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<CameraSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::CameraController>());
	myManager.setSystemSignature<CameraControllerSystem>(signature);

	
	// Creting our cool word
	//world = std::vector<Entity>(MAX_ENTITIES);
	Entity object;
	Entity camera;
	Entity cameraController;

	//Land Entity
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("land"),myStore->getMaterialPointer("landProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 30,3,20 }, { 0,0,0 }, { 1000,1000,1000 }));
	world.push_back(object);
	//Wolf Entity
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("wolf"),myStore->getMaterialPointer("wolfProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 20,5,10 }, { 0,0,0 }, { 2,2,2 }));
	world.push_back(object);
	//Tree 1 Entity
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("tree"),myStore->getMaterialPointer("treeProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 30,3,20 }, { 0,0,0 }, { 2,2,2 }));
	world.push_back(object);
	//Tree 2 Entity
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("tree"),myStore->getMaterialPointer("treeProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 40,3,-10 }, { 0,0,0 }, { 2,2,2 }));
	world.push_back(object);
	// Entity 6 (Camera)
	camera = myManager.createEntity();
	myManager.addComponentData<Camera>(camera, famm::Camera(
		{
			1,
			{0,0,0},
			0.01f,
			100.0f,
			16.0/9.0,
			glm::radians(90.0f),
			2.0f,
			glm::radians(90.0f)
		}));
	myManager.addComponentData<Transform>(camera, famm::Transform({ 10, 10, 10 }, { -10, -10, -10 }));


	// Entity 7 (Camera controller)
	cameraController = myManager.createEntity();
	myManager.addComponentData<CameraController>(cameraController, famm::CameraController({ camera,{3.0f, 3.0f, 3.0f},0.01f,0.01f,glm::pi<float>() / 10,5.0f,false}));


	glClearColor(0.768, 0.964, 0.992, 0);
}


void famm::Game::onDraw(double deltaTime) {
	std::shared_ptr<RendererSystem> RS = std::static_pointer_cast<RendererSystem>(mySystems[0]);
	std::shared_ptr <CameraSystem> CS = std::static_pointer_cast<CameraSystem>(mySystems[1]);
	std::shared_ptr<CameraControllerSystem> CCS = std::static_pointer_cast<CameraControllerSystem>(mySystems[2]);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!isPaused)
	{
		CCS->moveCamera(&myManager, deviceManager, deltaTime, CS);
		RS->drawEnities(&myManager, CS);
	}
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused)) onPause();
	if ((deviceManager->pressedActionChecker(famm::ControlsActions::DEV, famm::PressModes::JUST_PRESSED) && !isPaused)) developementMode = !developementMode;
}

void famm::Game::onImmediateGui(ImGuiIO* io)
{
	if (developementMode)
	{
		io->WantCaptureMouse = true;

		if (ImGui::TreeNode("Transformation")) {
			/*if (node->mesh.has_value()) {
				our::PairIteratorCombo("Mesh", node->mesh.value(), meshes.begin(), meshes.end());
				ImGui::ColorEdit4("Tint", glm::value_ptr(node->tint));
			}*/
			//char num_char[5 + sizeof(char)];
			static std::string translateString = "Translation##";
			static std::string rotateString = "Rotation##";
			static std::string scaleString = "Scale##";

			for (int i =0; i<world.size();i++)
			{
				std::string entityString = std::to_string(world[i]);

				auto& myTransformComponent = myManager.getComponentData<famm::Transform>(world[i]);
				ImGui::Text(entityString.c_str());
				
				ImGui::DragFloat3((translateString + entityString).c_str(), glm::value_ptr(myTransformComponent.position), 0.1f);
				ImGui::DragFloat3((rotateString + entityString).c_str(), glm::value_ptr(myTransformComponent.rotation), 0.01f);
				ImGui::DragFloat3((scaleString + entityString).c_str(), glm::value_ptr(myTransformComponent.scale), 0.1f);


				ImGui::Separator();
			}
			//glm::vec3 translation = { 0,0,0 }, rotation = { 0,0,0 }, scale = { 0,0,0 };
			
			/*	for (auto& [name, child] : node->children) {
					displayNodeGui(child, name);
				}*/
			ImGui::TreePop();
		}

		ImGui::Begin("New Model");
		//int max_element = (int)vertices.size() - 1;
		//float speed = 1.0f / (float)(max_element + 1);
		int max_element = 0;
		float speed = 0;

		//std::optional<std::string> model("wolf");
		//std::vector<std::string> models = {"wolf","tree"};
		std::vector<std::string> models = {"wolf","tree","land"};
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
				object = myManager.createEntity();
				myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer(models[item_current_idx].c_str()),myStore->getMaterialPointer("myProgram") }));
				myManager.addComponentData<Transform>(object, famm::Transform(translation,rotation,scale));
				world.insert(std::begin(world) + index, object);
			},
			[&](size_t index) { 
				myManager.destroyEntity(world[index]);
				world.erase(std::begin(world) + index); 
			});
		ImGui::End();
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