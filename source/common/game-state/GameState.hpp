#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <DeviceManager.hpp>

namespace famm {

	class GameState
	{
	public:

		virtual void onEnter() {};
		virtual void onDraw() {};
		virtual void onExit() {};

		virtual void pause() {};
		virtual void resume() {};
	};
	


}
#endif