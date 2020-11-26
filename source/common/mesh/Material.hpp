#include <map>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>

#include <glad/gl.h>

#include "vertex-attributes.hpp"

#include "mesh.hpp"
#include "shader.hpp"
#include "string.h"
#include <vector>
using namespace std;
namespace famm {
	//Material Class
	class Material {
		 
		private:
			ShaderProgram* s; // Pointer to the shader

			vector<pair<string, float>>UniformScalar; // Vector of uniform values (scalar) 
			vector<pair<string, float>>UniformVector2; // Vector of uniform vectors(2)
			vector<pair<string, float>>UniformVector3; // Vector of uniform vector(3) 
			
			int ScalarN; // number of scalar uniform values
			int Vector2N;  // number of ventor(2) uniform values
			int Vector3N; // number of vector(3) uniform vales

			string p; //Path
	public:
		 void onintalizeShader() {};

		 void addToScalar(string name, float variable);
		 void addToVector2(string name, float variable);
		 void addToVector3(string name, float variable);


		 void onDrawShader() {};
		 void onupdateshaderScalar() {};
		 void  onupdateshaderVector2() {};
		void  onupdateshaderVector3() {};
		 void onDestroyShader() {};






	};

}