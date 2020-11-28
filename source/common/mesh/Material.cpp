#include "Material.hpp"
#include <vector>


// pairing the values with their names and giving them size

famm::Material::Material(ShaderProgram* shader){
	s = shader;
}

// intializing shader
//void famm::Material::onintalizeShader() {
//	//s->create();
//	//s->attach(p, GL_VERTEX_SHADER);      //attaching with vertex shader
//	//s->attach(p, GL_FRAGMENT_SHADER);        // atttaching with fragment shader
//	//s->link();
//
//
//
//}




//Update the whole or part of Uniform vector given vector

//void famm::Material::updateShaderScalar(vector<pair<GLuint, float>> array1,int check)
//{
//	
//
//	// for looping on the unifrom scalar and inserting the values if its not the value of check
//
//	for (int i = 0; i < UniformScalar.size(); i++)
//	{
//		if (array1[i].second != check)
//		{
//
//			UniformScalar[i] = array1[i];
//
//		}
//	}
//
//
//
//}
//
//
//void famm::Material::updateShaderVector2(vector<pair<GLuint, glm::vec2>> array2,int check)
//
//{
//
//		// for looping on the unifrom vector 2 and inserting the values if its not the value of check
//	for (int i = 0; i < UniformVector2.size(); i++)
//	{
//	
//		if (array2[i].second[0] != check)
//		{
//
//			UniformVector2[i] = array2[i];
//
//		}
//	
//	
//	}
//
//
//
//}
//
//
//
//void famm::Material::updateShaderVector3(vector<pair<GLuint, glm::vec3>> array3,int check)
//{
//	
//
//	// for looping on the unifrom vector 3 and inserting the values if its not the value of check if we want to update a part of vector not the whole of it
//	for (int i = 0; i < UniformVector3.size(); i++)
//	{
//
//		if (array3[i].second[0] != check)
//		{
//
//			UniformVector3[i] = array3[i];
//
//		}
//
//
//	}
//
//
//
//
//}


//Update single value given value for a given  position 


void famm::Material::updateSingleShaderScalar(float value, GLuint location)
{
	UniformScalar[location] = value;
}

void famm::Material::updateSingleShaderVector2(glm::vec2 value, GLuint location)
{
	UniformVector2[location] = value;
}

void famm::Material::updateSingleShaderVector3(glm::vec3 value, GLuint location)
{
	UniformVector3[location] = value;
}

void  famm::Material::updateSingleShaderVector4(glm::vec4 value, GLuint location)
{
	UniformVector4[location] = value;
}

void  famm::Material::updateSingleShaderMatrix4(glm::mat4 value, GLuint location)
{
	UniformMatrix4[location] = value;
}


// filling the scalar vector
void famm::Material::addToScalar(std::string name, float variable)
{
	UniformScalar[s->getUniformLocation(name)]= variable;
}
// filling vector(2) vector
void famm::Material::addToVector2(std::string name, glm::vec2 variable)
{
	UniformVector2[s->getUniformLocation(name)] = variable;
}
// filling vector(3) vector
void famm::Material::addToVector3(std::string name, glm::vec3 variable)
{
	UniformVector3[s->getUniformLocation(name)] = variable;
}

void famm::Material::addToVector4(std::string name, glm::vec4 variable)
{
	UniformVector4[s->getUniformLocation(name)] = variable;
}

void famm::Material::addToMatrix4(std::string name, glm::mat4 variable)
{
	UniformMatrix4[s->getUniformLocation(name)] = variable;
}


//
//void famm::Material::onDestroyShader()
//{
//
//
//
//	s->destroy();
//
//
//
//}

//void famm::Material::onDrawShader()
//{
//
//	glUseProgram(*s);
//
//
//}
// updating shader of uniform scalar vector

//void famm::Material::onUpdateShaderScalar()
//{
//	// loop on the size of the vector
//	for (int i = 0; i < UniformScalar.size(); i++)
//	{
//		glUniform1f(UniformScalar[i].first, UniformScalar[i].second); // the value
//
//	}
//
//}
//
//
//void famm::Material::onUpdateShaderVector2()
//{
//	// loop on the size of the vector
//	for (int i = 0; i < UniformVector2.size(); i++)
//	{
//		glUniform2f(UniformScalar[i].first, UniformVector2[i].second.x, UniformVector2[i].second.y); // the value
//	}
//
//}
//
//
//
//void famm::Material::onUpdateShaderVector3()
//{
//	// loop on the size of the vector
//	for (int i = 0; i < UniformVector3.size(); i++)
//	{
//		glUniform3f(UniformScalar[i].first, UniformVector3[i].second.x, UniformVector3[i].second.y, UniformVector3[i].second.z); // the value
//	
//	}
//
//}
//


