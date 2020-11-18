#include "GameStateManager.hpp"

void famm::GameStateManager::onInitilaize() {
	currentState = new famm::PlayState();
}

void famm::GameStateManager::onDraw() {
	currentState->onEnter();
}


