#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include <game-state/GameState.hpp>
#include <application/Game.hpp>

namespace famm {

	class PlayState : public famm::GameState {
		famm::Game* game;
		double last_frame_time;
	public:
		PlayState(DeviceManager* deviceManager, Store* myStore){
			game = new famm::Game(deviceManager, myStore);
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