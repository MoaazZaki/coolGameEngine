#include "GameStateManager.hpp"

void famm::GameStateManager::onInitilaize() {
	currentState = new famm::PlayState(&deviceManager);
	currentState->onEnter();
}

void famm::GameStateManager::onDraw() {
	while (!glfwWindowShouldClose(deviceManager.getWindow())) {
		currentState->onDraw();
	}

	onDestroy();
}


void famm::GameStateManager::onDestroy()
{
	currentState->onExit();
	// Destroy the window
	deviceManager.destroyWindow();
	// And finally terminate GLFW
	glfwTerminate();
}