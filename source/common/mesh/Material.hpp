#ifndef MATERIAL_H
#define MATERIAL_H


#include "shader.hpp"
#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

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

	public:	

		Material(ShaderProgram* shader);

		// void onintalizeShader() {};

		void addToScalar(std::string name, float variable);
		void addToVector2(std::string name, glm::vec2 variable);
		void addToVector3(std::string name, glm::vec3 variable);
		void addToVector4(std::string name, glm::vec4 variable);
		void addToMatrix4(std::string name, glm::mat4 variable);

		//void updateShaderScalar(vector<pair<GLuint, float>> array1,int check); //Update the whole or part of Uniform vector given vector 
		//void  updateShaderVector2(vector<pair<GLuint, glm::vec2>> array2, int check);
		//void  updateShaderVector3(vector<pair<GLuint, glm::vec3>> array3, int check);

		void updateSingleShaderScalar(float value, GLuint location); //Update single value given value and position 
		void  updateSingleShaderVector2(glm::vec2 value, GLuint location);
		void  updateSingleShaderVector3(glm::vec3 value, GLuint location);
		void  updateSingleShaderVector4(glm::vec4 value, GLuint location);
		void  updateSingleShaderMatrix4(glm::mat4 value, GLuint location);
		//void onDrawShader() {};
		//void onUpdateShaderScalar();
		//void  onUpdateShaderVector2();
		//void  onUpdateShaderVector3();
		// void onDestroyShader() {};

		ShaderProgram* getShaderProgram() { return s; }




	};

}
#endif
