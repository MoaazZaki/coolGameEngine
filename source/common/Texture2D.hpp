#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <texture/texture-utils.h>

namespace famm
{
    class Texture2D
    {
        GLuint texture;
        glm::ivec2 imageSize;

    public:
        Texture2D() { texture = 0; imageSize = { 0,0 }; }
        void create();
        void destroy();

        void loadTexture(const char* filename, bool generate_mipmap = true, bool colored = true);
        void loadTexture(Color color = { 255,255,255,255 }, glm::ivec2 size = { 1,1 });
        void loadTexture(glm::ivec2 size, glm::ivec2 patternSize, famm::Color color1, famm::Color color2);

        void bindTexture(GLuint unit);

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Texture2D(Texture2D const&) = delete;
        Texture2D& operator=(Texture2D const&) = delete;
    };
}


#endif