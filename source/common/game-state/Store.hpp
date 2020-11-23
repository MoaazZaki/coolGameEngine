#ifndef STORE_H
#define STORE_H

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>



#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <shader.hpp>

#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "DeviceManager.hpp"


namespace famm {

	class Store
	{
	private:

		DeviceManager* deviceManager;
		ImGuiIO io;
		std::unordered_map<std::string, ShaderProgram*> tableOfShaderPrograms;

	public:
		Store(DeviceManager* deviceManager) {
			this->deviceManager = deviceManager;
		}

		

		void startInit();

		void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.
		//void setupCallbacks(GLFWwindow* window);
		//void deviceManagerCallbacks(CallbacksModes mode, int param1, int param2, int param3, int param4);

		ImGuiIO* getImGuiObject() { return &io; }
	};



}
#endif