#include "playState.hpp"


void famm::PlayState::onEnter(){
	last_frame_time = glfwGetTime();
	int exitStatus = game->startInit();
}

void famm::PlayState::onDraw() {
	//int exitStatus = game.run();
	int exitStatus = game->startLoop(last_frame_time);
}

void famm::PlayState::onExit() {
	game->startCleaning();
}
