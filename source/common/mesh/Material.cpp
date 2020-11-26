#include "Material.hpp"
#include <vector>


// pairing the values with their names and giving them size

famm::Material::Material(int ScalarN,int Vector2N,int Vector3N)
{    // pairing name with values using size
	UniformScalar =  vector<pair<char*, float>>(ScalarN);
	UniformVector2 = vector<pair<char*, glm::vec2>>(Vector2N);
	UniformVector3 = vector<pair<char*, glm::vec3>>(Vector3N);


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


// filling the scalar vector
void famm::Material::addToScalar(char* name, float variable)
{
	UniformScalar.push_back(std::make_pair(name, variable));



}
// filling vector(2) vector
void famm::Material::addToVector2(char* name, glm::vec2 variable)
{

	UniformVector2.push_back(std::make_pair(name, variable));

}
// filling vector(3) vector

void famm::Material::addToVector3(char* name, glm::vec3 variable)
{

	UniformVector3.push_back(std::make_pair(name, variable));

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

void famm::Material::onUpdateShaderScalar()
{
	// loop on the size of the vector
	for (int i = 0; i < UniformScalar.size(); i++)
	{
		GLuint G = glGetUniformLocation(*s,UniformScalar[i].first); // the name
		glUniform1f(G, UniformScalar[i].second); // the value

	}

}


void famm::Material::onUpdateShaderVector2()
{
	// loop on the size of the vector
	for (int i = 0; i < UniformVector2.size(); i++)
	{
		GLuint G = glGetUniformLocation(*s, UniformVector2[i].first); // the name
		glUniform2f(G, UniformVector2[i].second.x, UniformVector2[i].second.y); // the value

	}

}



void famm::Material::onUpdateShaderVector3()
{
	// loop on the size of the vector
	for (int i = 0; i < UniformVector3.size(); i++)
	{
		GLuint G = glGetUniformLocation(*s,UniformVector3[i].first); // the name
		glUniform3f(G, UniformVector3[i].second.x, UniformVector3[i].second.y, UniformVector3[i].second.z); // the value
	
	}

}



