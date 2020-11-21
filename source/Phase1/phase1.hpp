#ifndef PHASEONE_H
#define PHASEONE_H


#include <application.hpp>
#include <shader.hpp>
namespace famm {
	class PhaseOneApplication : public famm::Application {
	private:
		famm::ShaderProgram program_heart, program_smiley, program_pacman, program_g;
		GLuint vertex_array;

		glm::vec2 cursorPos;
		glm::float32 windowRatio;

		GLuint currentShape;
		
		bool isPaused;

		bool inputButtonFlags[6] = { false,false,false,false,false,false };
		
	public:
		PhaseOneApplication(DeviceManager* deviceManager):Application(deviceManager){}

		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;
		void onImmediateGui(ImGuiIO& io) override;

		void onPause();
		void onResume();

		void changeCurrentShape(famm::ControlsActions action);

		bool statePaused() override;
	};
}
#endif