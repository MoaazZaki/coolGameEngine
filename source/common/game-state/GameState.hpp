#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace famm {

	class GameState
	{
	public:

		virtual void onEnter() {};
		virtual void onDraw() {};
		virtual void onExit() {};

		virtual void Pause() {};
		virtual void Resume() {};
	};
	


}
#endif