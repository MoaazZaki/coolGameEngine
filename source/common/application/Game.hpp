#ifndef GAME_H
#define GAME_H

#include <application.hpp>
#include <ECSManager.hpp>
#include <Components/Components.hpp>

#include <RenderedSystem.hpp>
#include <CameraControllerSystem.hpp>


namespace famm {
	class Game : public famm::Application {
	private:
		ECSManager myManager;

		std::vector<Entity> world;

		std::vector<std::shared_ptr<System>> mySystems;

		bool isPaused = false;

	public:
		Game(DeviceManager* deviceManager, Store* myStore) : Application(deviceManager, myStore) { isPaused = false;}

		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;
		//void onImmediateGui(ImGuiIO* io) override;

		void onPause() { isPaused = true; }
		void onResume() { isPaused = false; }

		bool statePaused() override { return isPaused; }

	};
}

#endif
