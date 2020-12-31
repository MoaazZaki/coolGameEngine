#ifndef MATERIAL_H
#define MATERIAL_H


#include "shader.hpp"
#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include<Texture2D.hpp>
#include<Sampler.hpp>
namespace famm {
	//Material Class
	class Material {
		 
		private:
			ShaderProgram* s; // Pointer to the shader
			
			std::unordered_map<GLuint, float> UniformScalar; // Vector of uniform values (scalar) 
			std::unordered_map<GLuint, glm::vec2> UniformVector2; // Vector of uniform vectors(2)
			std::unordered_map<GLuint, glm::vec3> UniformVector3; // Vector of uniform vector(3) 
			std::unordered_map<GLuint, glm::vec4> UniformVector4; // Vector of uniform vector(4)
			std::unordered_map<GLuint, glm::mat4> UniformMatrix4; // Vector of uniform vector(4)
			std::unordered_map<std::string,GLuint> locationMap;
			
			std::vector<std::pair<Texture2D*, Sampler*>> materialTextures;

	public:	

		Material(ShaderProgram* shader);

		// void onintalizeShader() {};

		void addProperty(std::string name, float variable);
		void addProperty(std::string name, glm::vec2 variable);
		void addProperty(std::string name, glm::vec3 variable);
		void addProperty(std::string name, glm::vec4 variable);
		void addProperty(std::string name, glm::mat4 variable);

		void updateProperty(std::string name,float value); //Update single value given value and position 
		void  updateProperty(std::string name,glm::vec2 value);
		void  updateProperty(std::string name,glm::vec3 value);
		void  updateProperty(std::string name,glm::vec4 value);
		void  updateProperty(std::string name,glm::mat4 value);
		
		void addTextureSampler(Texture2D* texture, Sampler* sampler);


		ShaderProgram* getShaderProgram() { return s; }
		std::vector<std::pair<Texture2D*, Sampler*>>& getMaterials() { return materialTextures; }

		GLuint getLocation(std::string name) {
			std::unordered_map<std::string, GLuint>::const_iterator location = locationMap.find(name);
			return location->second;
		}
		float getScalar(GLuint location) {
			std::unordered_map<GLuint,float>::const_iterator value = UniformScalar.find(location);
			return value->second;
		}
		glm::vec2 getVec2(GLuint location) {
			std::unordered_map<GLuint, glm::vec2>::const_iterator value = UniformVector2.find(location);
			return value->second;
		}
		glm::vec3 getVec3(GLuint location) {
			std::unordered_map<GLuint, glm::vec3>::const_iterator value = UniformVector3.find(location);
			return value->second;
		}
		glm::vec4 getVec4(GLuint location) {
			std::unordered_map<GLuint, glm::vec4>::const_iterator value = UniformVector4.find(location);
			return value->second;
		}
		glm::mat4 getMat4(GLuint location) {
			std::unordered_map<GLuint, glm::mat4>::const_iterator value = UniformMatrix4.find(location);
			return value->second;
		}

		void destroy()
		{
			UniformScalar.clear();
			UniformVector2.clear();
			UniformVector3.clear();
			UniformVector4.clear();
			UniformMatrix4.clear();
			locationMap.clear();
			materialTextures.clear();

		}

		//Delete copy constructor and assignment operation
		//This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
		//So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
		Material(Material const&) = delete;
		Material& operator=(Material const&) = delete;
	};

}
#endif
