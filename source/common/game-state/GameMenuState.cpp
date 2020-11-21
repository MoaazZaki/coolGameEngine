#include "GameMenuState.hpp"


void famm::GameMenuState::onEnter() {
	bool static firstTime = true;
	if (firstTime)
	{
		menu->startInit();
		firstTime = false;
	}
	last_frame_time = glfwGetTime();
}
void famm::GameMenuState::onDraw() {
	menu->startLoop(last_frame_time);
}
void famm::GameMenuState::onExit() {
	menu->startCleaning();
}