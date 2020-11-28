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
	auto cameraControllerSystem = myManager.addSystem<famm::CameraControllerSystem>();\
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
	// Entity 0 
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 0,-1,0 }, { 0,0,0 }, { 11,2,11 }));


	// Entity 1 
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ -4,1,-4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 2
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 4,1,-4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 3
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ -4,1,4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 4
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 4,1,4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 5 (Triangle)
	object = myManager.createEntity();
	myManager.addComponentData<MeshRenderer>(object, famm::MeshRenderer({ myStore->getMeshPointer("triangle"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(object, famm::Transform({ 0,1,0 }, { 0,0,0 }, { 2,2,2 }));


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


	glClearColor(0, 0, 0, 0);
}


void famm::Game::onDraw(double deltaTime) {
	std::shared_ptr<RendererSystem> RS = std::static_pointer_cast<RendererSystem>(mySystems[0]);
	std::shared_ptr <CameraSystem> CS = std::static_pointer_cast<CameraSystem>(mySystems[1]);
	std::shared_ptr<CameraControllerSystem> CCS = std::static_pointer_cast<CameraControllerSystem>(mySystems[2]);

	CCS->moveCamera(&myManager, deviceManager, deltaTime, CS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RS->drawEnities(&myManager, CS);
}


void famm::Game::onDestroy() {}