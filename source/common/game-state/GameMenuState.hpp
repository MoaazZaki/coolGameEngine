#ifndef GAMEMENUSTATE_H
#define GAMEMENUSTATE_H

#include <game-state/GameState.hpp>
#include <../Phase1/phase1.hpp>
#include <../common/application/GameMenu.hpp>

namespace famm {

	class GameMenuState : public famm::GameState {
		famm::GameMenu* menu;
		double last_frame_time;
	public:
		GameMenuState(DeviceManager* deviceManager) {
			menu = new famm::GameMenu(deviceManager);
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