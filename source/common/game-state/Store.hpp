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
#include <mesh/mesh.hpp>
#include <mesh/Material.hpp>
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>

namespace famm {

	class Store
	{
	private:

		DeviceManager* deviceManager;
		ImGuiIO io;
		std::unordered_map<std::string, ShaderProgram*> tableOfShaderPrograms;
		std::unordered_map<std::string, Mesh*> tableOfMeshes;
		std::unordered_map<std::string, Material*> tableOfMaterials;

	public:
		Store(DeviceManager* deviceManager) {
			this->deviceManager = deviceManager;
		}

		

		void startInit();

		void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.
		//void setupCallbacks(GLFWwindow* window);
		//void deviceManagerCallbacks(CallbacksModes mode, int param1, int param2, int param3, int param4);

		ImGuiIO* getImGuiObject() { return &io; }
		ShaderProgram* getShaderPointer(std::string name) {	
			std::unordered_map<std::string, ShaderProgram*>::const_iterator shader = tableOfShaderPrograms.find(name);
			return shader->second;
		}

		Mesh* getMeshPointer(std::string name) {
			std::unordered_map<std::string, Mesh*>::const_iterator mesh = tableOfMeshes.find(name);
			return mesh->second;
		}

		Material* getMaterialPointer(std::string name) {
			std::unordered_map<std::string, Material*>::const_iterator material = tableOfMaterials.find(name);
			return material->second;
		}

		void startCleaning();
	};



}
#endif