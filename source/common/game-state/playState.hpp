#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include <game-state/GameState.hpp>
#include <../Phase1/phase1.hpp>

namespace famm {

	class PlayState : public famm::GameState {
		famm::PhaseOneApplication game;
	public:
		void onEnter() override;

	};

}

#endif