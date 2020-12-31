#include "Texture2D.hpp"

void famm::Texture2D::create()
{
	glGenTextures(1, &texture);
}

void famm::Texture2D::destroy()
{
	glDeleteTextures(1, &texture);
}
void famm::Texture2D::loadTexture(const char* filename, bool generate_mipmap, bool colored)
{
	if (colored)
		imageSize = famm::texture_utils::loadImage(texture, filename, generate_mipmap);
	else
		imageSize = famm::texture_utils::loadImageGrayscale(texture, filename, generate_mipmap);
}
void famm::Texture2D::loadTexture(Color color, glm::ivec2 size )
{
	imageSize = size;
	famm::texture_utils::singleColor(texture, color, size);
}
void famm::Texture2D::loadTexture(glm::ivec2 size, glm::ivec2 patternSize, famm::Color color1, famm::Color color2)
{
	imageSize = patternSize;
	famm::texture_utils::checkerBoard(texture, size, patternSize, color1, color2);
}
void famm::Texture2D::bindTexture(GLuint unit)
{
	glActiveTexture(unit + GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}
