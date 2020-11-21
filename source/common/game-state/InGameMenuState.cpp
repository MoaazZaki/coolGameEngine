#include "InGameMenuState.hpp"


void famm::InGameMenuState::onEnter() {
	menu->onInitialize();
	last_frame_time = glfwGetTime();
}
void famm::InGameMenuState::onDraw() {
	menu->startLoop(last_frame_time);
}
void famm::InGameMenuState::onExit() {
	menu->onDestroy();
}