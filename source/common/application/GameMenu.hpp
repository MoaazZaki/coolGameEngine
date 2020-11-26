#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <application.hpp>

namespace famm {
	class GameMenu : public famm::Application {
	private:
		bool inputButtonFlags[6] = { false,false,false,false,false,false };
		bool isPaused;
		bool isTerminated;
	public:
		GameMenu(DeviceManager* deviceManager,Store* myStore) : Application(deviceManager, myStore) { isPaused = false; isTerminated = false; }

		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;
		void onImmediateGui(ImGuiIO* io) override;

		//void onPause();
		//void onResume();


		void onPause();
		void onResume();

		bool statePaused() override;
		bool stateTerminated() override;

	};
}



#endif