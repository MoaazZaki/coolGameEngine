#include "playState.hpp"


void famm::PlayState::onEnter(){
	game->onInitialize();
	last_frame_time = glfwGetTime();

}

void famm::PlayState::onDraw() {
	//int exitStatus = game.run();
	int exitStatus = game->startLoop(last_frame_time);
}

void famm::PlayState::onExit() {
	game->onDestroy();
}

bool famm::PlayState::statePaused()
{
	return game->statePaused();
}
