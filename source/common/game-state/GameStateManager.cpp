#include "GameStateManager.hpp"

void famm::GameStateManager::onInitilaize() {
	currentState = new famm::GameMenuState(&deviceManager);
	
}

void famm::GameStateManager::onDraw() {
	while (!glfwWindowShouldClose(deviceManager.getWindow())) {
		currentState->onDraw();

		if (currentState->statePaused())
		{
			if(PlayState* d = dynamic_cast<PlayState*>(currentState))
			{ 
				pausedState = currentState;
				currentState = new famm::InGameMenuState(&deviceManager);
			}
			else if (InGameMenuState* d = dynamic_cast<InGameMenuState*>(currentState))
			{
				delete currentState;
				currentState = pausedState;
				currentState->resume();
				pausedState = NULL;
			}
			else
			{
				pausedState = currentState;
				currentState = new famm::PlayState(&deviceManager);
				delete pausedState;
				pausedState = NULL;
			}
		}
		if (!deviceManager.getWindowSettings().isRefreshed) //If changed resolution of fullscreen
		{
			deviceManager.refreshWidow();
			currentState->resume();
			//currentState->onEnter();
		} 

		if (currentState->stateTerminated())
		{
			if (GameMenuState* d = dynamic_cast<GameMenuState*>(currentState))
			{
				break;
			}
			else if (InGameMenuState* d = dynamic_cast<InGameMenuState*>(currentState))
			{
				if (pausedState) delete pausedState;
				delete currentState;
				currentState = new famm::GameMenuState(&deviceManager);
			}
		}
	}

	onDestroy();
}


void famm::GameStateManager::onDestroy()
{
	currentState->onExit();

	if (currentState != NULL) delete currentState;

	// Destroy the window
	deviceManager.destroyWindow();
	// And finally terminate GLFW
	glfwTerminate();
}