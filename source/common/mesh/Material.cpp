#include "Material.hpp"
#include <vector>


// pairing the values with their names and giving them size

famm::Material::Material()
{    // pairing name with values using size
	UniformScalar = new vector<pair<string, float>>(ScalarN);  
	UniformVector2= new vector<pair<string, float>>(Vector2N);
	UniformVector3= new vector<pair<string, float>>(Vector3N);


}

// intializing shader
void famm::Material::onintalizeShader() {
	s->create();
	s->attach(p, GL_VERTEX_SHADER);      //attaching with vertex shader
	s->attach(p, GL_FRAGMENT_SHADER);        // atttaching with fragment shader
	s->link();



}
// filling the scalar vector
void famm::Material::addToScalar(string name, float variable)
{
	UniformScalar.push_back(std::make_pair(name, variable));



}
// filling vector(2) vector
void famm::Material::addToVector2(string name, float variable)
{

	UniformVector2.push_back(std::make_pair(name, variable));

}
// filling vector(3) vector

void famm::Material::addToVector3(string name, float variable)
{

	UniformVector3.push_back(std::make_pair(name, variable));

}





void famm::Material::onDestroyShader()
{



	s->destroy();



}

void famm::Material::onDrawShader()
{

	glUseProgram(*s);


}
// updating shader of uniform scalar vector

void famm::Material::onupdateshaderScalar()
{
	// loop on the size of the vector
	for (int i = 0; i < ScalarN; i++)
	{
		GLuint G = glGetUniformLocation(*s,* UniformScalar[i].first); // the name
		glUniform1f(G, UniformScalar[i].second); // the value

	}

}


void famm::Material::onupdateshaderVector2()
{
	// loop on the size of the vector
	for (int i = 0; i < Vector2N; i++)
	{
		GLuint G = glGetUniformLocation(*s, *UniformVector2[i].first); // the name
		glUniform1f(G, UniformVector2[i].second); // the value

	}

}



void famm::Material::onupdateshaderVector3()
{
	// loop on the size of the vector
	for (int i = 0; i < Vector3N; i++)
	{
		GLuint G = glGetUniformLocation(*s, *UniformVector3[i].first); // the name
		glUniform1f(G, UniformVector3[i].second); // the value
	
	}

}



