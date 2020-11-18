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

	public:
		void onInitialize() override;
		void onDraw(double deltaTime) override;
		void onDestroy() override;

		famm::WindowConfiguration getWindowConfiguration() override;
	};
}
#endif