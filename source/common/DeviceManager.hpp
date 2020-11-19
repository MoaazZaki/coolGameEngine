#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <iostream>

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "input/keyboard.hpp"
#include "input/mouse.hpp"

namespace famm {

	enum class PressModes {IS_PRESSED,JUST_PRESSED,JUST_RELEASED};
	enum class CallbacksModes { KEY_EVENT, CURSOR_MOVE_EVENT, MOUSE_BUTTON_EVENT,SCROLL_EVENT};
	enum class ControlsActions {UP,DOWN,RIGHT,LEFT,SCREEN_SHOT};

	struct WindowSettings {
		const char* title;
		glm::i16vec2 size;
		bool isFullscreen;
	};

	struct ControlSettings{
		std::uint16_t up;
		std::uint16_t down;
		std::uint16_t right;
		std::uint16_t left;
		std::uint16_t screenShot;

		std::uint8_t sensitivity;
	};




	class DeviceManager {
	protected:
		GLFWwindow* window = nullptr;       // Pointer to the window created by GLFW using "glfwCreateWindow()".
		Keyboard keyboard;                  // Instance of "our" keyboard class that handles keyboard functionalities.
		Mouse mouse;                        // Instance of "our" mouse class that handles mouse functionalities.
		
		WindowSettings windowSettings;
		ControlSettings controlSettings;

	public:

		DeviceManager();
		void setupCallbacks(CallbacksModes mode, int param1, int param2, int param3, int param4);

		/// <summary>
		///	Window Realted functions
		/// </summary>
		int createNewWindow();
		void destroyWindow();
		void attachWindow();
		WindowSettings updateWindowSettings(bool isFullScreen,std::uint16_t width, std::uint16_t height);
		void swapWindowBuffers();

		/// <summary>
		///	Keyboard & Mouse Realted functions
		/// </summary>
		void updateInput();
		bool pressChecker(ControlsActions action,PressModes mode);
		std::uint16_t getCorrespondingKey(ControlsActions action);
		glm::vec2 getNormalizedMousePos();
		
		/// <summary>
		// Class Getters.
		/// </summary>
		GLFWwindow* getWindow() { return window; }
		[[nodiscard]] const GLFWwindow* getWindow() const { return window; }
		Keyboard& getKeyboard() { return keyboard; }
		[[nodiscard]] const Keyboard& getKeyboard() const { return keyboard; }
		Mouse& getMouse() { return mouse; }
		[[nodiscard]] const Mouse& getMouse() const { return mouse; }


		// Get the size of the frame buffer of the window in pixels.
		glm::ivec2 getFrameBufferSize() {
			glm::ivec2 size;
			glfwGetFramebufferSize(window, &(size.x), &(size.y));
			return size;
		}
		
		// Get the window size. In most cases, it is equal to the frame buffer size.
		// But on some platforms, the framebuffer size may be different from the window size.
		glm::ivec2 getWindowSize() {
			glm::ivec2 size;
			glfwGetWindowSize(window, &(size.x), &(size.y));
			return size;
		}

		famm::WindowSettings getWindowSettings()
		{
			return windowSettings;
		}


	};

}

#endif