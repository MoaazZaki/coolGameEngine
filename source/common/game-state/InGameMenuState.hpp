#ifndef INGAMEMENUSTATE_H
#define INGAMEMENUSTATE_H

#include <game-state/GameState.hpp>
#include <../Phase1/phase1.hpp>
#include <../common/application/InGameMenu.hpp>

namespace famm {

	class InGameMenuState : public famm::GameState {
		famm::InGameMenu* menu;
		double last_frame_time;
	public:
		InGameMenuState(DeviceManager* deviceManager, ImGuiIO* io){
			menu = new famm::InGameMenu(deviceManager,io);
			onEnter();
		}

		void onEnter() override;
		void onDraw() override;
		void onExit() override;


		bool statePaused()override { return menu->statePaused(); }
		bool stateTerminated()override { return menu->stateTerminated(); }

	};

}

#endif