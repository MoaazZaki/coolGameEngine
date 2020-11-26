#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include <game-state/GameState.hpp>
#include <../Phase1/phase1.hpp>

namespace famm {

	class PlayState : public famm::GameState {
		famm::PhaseOneApplication* game;
		double last_frame_time;
	public:
		PlayState(DeviceManager* deviceManager, Store* myStore){
			game = new famm::PhaseOneApplication(deviceManager, myStore);
			onEnter();
		}

		void onEnter() override;
		void onDraw() override;
		void onExit() override;

		void resume()override { game->onResume(); }


		bool statePaused() override;

	};

}

#endif