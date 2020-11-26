#include <map>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>

#include <glad/gl.h>
#include "shader.hpp"
#include "string.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
using namespace std;
namespace famm {
	//Material Class
	class Material {
		 
		private:
			ShaderProgram* s; // Pointer to the shader

			vector<pair<char*, float>> UniformScalar; // Vector of uniform values (scalar) 
			vector<pair<char*, glm::vec2>> UniformVector2; // Vector of uniform vectors(2)
			vector<pair<char*, glm::vec3>> UniformVector3; // Vector of uniform vector(3) 
	public:	

		Material(int ScalarN, int Vector2N, int Vector3N);

		// void onintalizeShader() {};

		void addToScalar(char* name, float variable);
		void addToVector2(char* name, glm::vec2 variable);
		void addToVector3(char* name, glm::vec3 variable);

		void updateShaderScalar(vector<pair<char*, float>> array); //Update the whole or part of Uniform vector given vector 
		void  updateShaderVector2(vector<pair<char*, glm::vec2>> array);
		void  updateShaderVector3(vector<pair<char*, glm::vec3>> array);

		void updateSingleShaderScalar(float value, int pos); //Update single value given value and position 
		void  updateSingleShaderVector2(glm::vec2 value, int pos);
		void  updateSingleShaderVector3(glm::vec3 value, int pos);

		//void onDrawShader() {};
		void onUpdateShaderScalar();
		void  onUpdateShaderVector2();
		void  onUpdateShaderVector3();
		// void onDestroyShader() {};

		ShaderProgram* getShaderProgram() { return s; }




	};

}