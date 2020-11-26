#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <memory>
#include <game-state\Store.hpp>
#include <game-state\GameState.hpp>
#include <game-state\PlayState.hpp>
#include <game-state\InGameMenuState.hpp>
#include <game-state\GameMenuState.hpp>


namespace famm {

	class GameStateManager
	{
	private:
		GameState* currentState;
		GameState* pausedState;
		GameState* nextState;

		DeviceManager deviceManager;
		Store myStore;
		
	public:
		
		GameStateManager():myStore(&deviceManager){}

		void onInitilaize();

		void onDraw();

		//void onSwitch();

		void onDestroy();
	};

	


}
#endif