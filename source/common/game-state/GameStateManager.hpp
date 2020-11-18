#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <memory>
#include <game-state\GameState.hpp>
#include <game-state\PlayState.hpp>

namespace famm {

	class GameStateManager
	{
	private:
		GameState* currentState;
		GameState* pausedState;
		GameState* nextState;

		
	public:
		
		void onInitilaize();

		void onDraw();

		//void onSwitch();

		//void onDestroy();
	};

	


}
#endif