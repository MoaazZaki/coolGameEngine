#ifndef GAME_H
#define GAME_H

#include <application.hpp>
#include <ECSManager.hpp>
#include <Components/Components.hpp>

#include <RenderedSystem.hpp>
#include <CameraControllerSystem.hpp>
#include <imgui-utils/utils.hpp>

struct componentJSON; // Forward decleration

namespace famm {
	class Game : public famm::Application {
	private:
		ECSManager myManager;

		std::vector<Entity> worldArray;

		std::vector<Entity> lightArray;

		std::vector<std::shared_ptr<System>> mySystems;

		bool isPaused = false;

		bool developementMode = false;
	public:
		Game(DeviceManager* deviceManager, Store* myStore) : Application(deviceManager, myStore) { isPaused = false;}

		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;

		void lightGui(ImGuiIO* io);
		void transformationGui(ImGuiIO* io);
		void newModelGui(ImGuiIO* io);
		void onImmediateGui(ImGuiIO* io) override;

		void onPause() { isPaused = true; }
		void onResume() { isPaused = false; }

		bool statePaused() override { return isPaused; }

		void extractWorld(const nlohmann::json& j, famm::Entity node, Store* myStore, ECSManager* myManager);

	};
}

#endif
