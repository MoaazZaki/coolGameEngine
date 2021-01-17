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
#include <fstream>
#include <json/json.hpp>

#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "DeviceManager.hpp"
#include <mesh/mesh.hpp>
#include <mesh/Material.hpp>
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
#include <Texture2D.hpp>
#include <Sampler.hpp>

#include <data-types.h>

namespace glm {
	template<length_t L, typename T, qualifier Q>
	void from_json(const nlohmann::json& j, vec<L, T, Q>& v) {
		for (length_t index = 0; index < L; ++index)
			v[index] = j[index].get<T>();
	}
}


namespace famm {



	class Store
	{
	private:

		DeviceManager* deviceManager;
		ImGuiIO io;
		std::unordered_map<std::string, ShaderProgram*> tableOfShaderPrograms;
		std::unordered_map<std::string, Mesh*> tableOfMeshes;
		std::unordered_map<std::string, Material*> tableOfMaterials;
		std::unordered_map<std::string, Texture2D*> tableOfTextures;
		std::unordered_map<std::string, Sampler*> tableOfSampelers;
	public:
		Store(DeviceManager* deviceManager) {
			this->deviceManager = deviceManager;
		}

		

		void startInit(std:: string path);

		void loadAssets(std:: string path);

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

		Texture2D* getTexturePointer(std::string name) {
			std::unordered_map<std::string, Texture2D*>::const_iterator material = tableOfTextures.find(name);
			return material->second;
		}

		Sampler* getSamplerPointer(std::string name) {
			std::unordered_map<std::string, Sampler*>::const_iterator material = tableOfSampelers.find(name);
			return material->second;
		}

		void startCleaning();


	};



}



//namespace glm {
//	template<length_t L, typename T, qualifier Q>
//	void from_json(const nlohmann::json& j, vec<L, T, Q>& v) {
//		for (length_t index = 0; index < L; ++index)
//			v[index] = j[index].get<T>();
//	}
//}


#endif