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
	auto cameraSystem = myManager.addSystem<famm::CameraSystem>();
	auto cameraControllerSystem = myManager.addSystem<famm::CameraControllerSystem>();

	// Setting signatures
	famm::Signature signature;
	signature.set(myManager.getComponentType<famm::MeshRenderer>());
	signature.set(myManager.getComponentType<famm::Transform>());
	myManager.setSystemSignature<rendererSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::Camera>());
	myManager.setSystemSignature<cameraSystem>(signature);

	signature.reset();
	signature.set(myManager.getComponentType<famm::CameraController>());
	myManager.setSystemSignature<cameraControllerSystem>(signature);

	
	// Creting our cool word
	world = std::vector<Entity>(MAX_ENTITIES);

	// Entity 0 
	myManager.addComponentData<MeshRenderer>(world[0], famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[0], famm::Transform({ 0,-1,0 }, { 0,0,0 }, { 11,2,11 }));

	// Entity 1 
	myManager.addComponentData<MeshRenderer>(world[1], famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[1], famm::Transform({ -4,1,-4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 2
	myManager.addComponentData<MeshRenderer>(world[2], famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[2], famm::Transform({ 4,1,-4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 3
	myManager.addComponentData<MeshRenderer>(world[3], famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[3], famm::Transform({ -4,1,4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 4
	myManager.addComponentData<MeshRenderer>(world[4], famm::MeshRenderer({ myStore->getMeshPointer("model"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[4], famm::Transform({ 4,1,4 }, { 0,0,0 }, { 2,2,2 }));

	// Entity 5 (Triangle)
	myManager.addComponentData<MeshRenderer>(world[5], famm::MeshRenderer({ myStore->getMeshPointer("triangle"),myStore->getMaterialPointer("myProgram") }));
	myManager.addComponentData<Transform>(world[5], famm::Transform({ 0,1,0 }, { 0,0,0 }, { 2,2,2 }));


	// Entity 6 (Camera)
	myManager.addComponentData<Camera>(world[6], famm::Camera(
		{
			0,
			1,
			{0,0,0},
			{0,0,0},
			{0,0,0},
			0.01f,
			100.0f,
			1.0f,
			glm::radians(90.0f),
			2.0f,
			glm::radians(90.0f)
		}));
	cameraSystem->setEyePosition({ 10, 10, 10 });
	cameraSystem->setTarget({ 0, 0, 0 });
	cameraSystem->setUp({ 0, 1, 0 });

	// Entity 7 (Camera controller)
	myManager.addComponentData<CameraController>(world[7], famm::CameraController({ 0,{3.0f,3.0f,3.0f} }));
	//cameraControllerSystem->moveCamera();
}