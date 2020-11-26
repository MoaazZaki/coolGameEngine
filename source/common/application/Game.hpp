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
	public:
		Game(DeviceManager* deviceManager, Store* myStore) : Application(deviceManager, myStore) { isPaused = false; isTerminated = false; }

		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;
		//void onImmediateGui(ImGuiIO* io) override;

		void onPause();
		void onResume();

		bool statePaused() override;
		bool stateTerminated() override;


	};
}
