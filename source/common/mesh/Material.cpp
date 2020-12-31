#include "Material.hpp"
#include <vector>


// pairing the values with their names and giving them size

famm::Material::Material(ShaderProgram* shader){
	s = shader;
}


void famm::Material::updateProperty(std::string name , float value)
{
	UniformScalar[locationMap[name]] = value;
}

void famm::Material::updateProperty(std::string name , glm::vec2 value)
{
	UniformVector2[locationMap[name]] = value;
}

void famm::Material::updateProperty(std::string name , glm::vec3 value)
{
	UniformVector3[locationMap[name]] = value;
}

void  famm::Material::updateProperty(std::string name , glm::vec4 value)
{
	UniformVector4[locationMap[name]] = value;
}

void  famm::Material::updateProperty(std::string name , glm::mat4 value)
{
	UniformMatrix4[locationMap[name]] = value;
}


// filling the scalar vector
void famm::Material::addProperty(std::string name, float variable)
{
	GLuint location = s->getUniformLocation(name);
	locationMap[name] = location;
	UniformScalar[location]= variable;
}
// filling vector(2) vector
void famm::Material::addProperty(std::string name, glm::vec2 variable)
{
	GLuint location = s->getUniformLocation(name);
	locationMap[name] = location;
	UniformVector2[location] = variable;
}
// filling vector(3) vector
void famm::Material::addProperty(std::string name, glm::vec3 variable)
{
	GLuint location = s->getUniformLocation(name);
	locationMap[name] = location;
	UniformVector3[location] = variable;
}

void famm::Material::addProperty(std::string name, glm::vec4 variable)
{
	GLuint location = s->getUniformLocation(name);
	locationMap[name] = location;
	UniformVector4[location] = variable;
}

void famm::Material::addProperty(std::string name, glm::mat4 variable)
{
	GLuint location = s->getUniformLocation(name);
	locationMap[name] = location;
	UniformMatrix4[location] = variable;
}


void famm::Material::addTextureSampler(Texture2D* texture, Sampler* sampler)
{
	materialTextures.push_back(std::make_pair(texture, sampler));
}