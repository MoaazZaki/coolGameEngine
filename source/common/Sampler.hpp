#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace famm
{
    class Sampler
    {
        GLuint sampler;
        GLenum magnification_filter , minification_filter ;
        GLenum wrap_s, wrap_t ;
        glm::vec4 border_color;
        GLfloat max_anisotropy;

    public:
        void bindSampler(GLuint unit);
        void setMagnificationFilter(GLenum mf);
        void setMinificationFilter(GLenum mf);
        void setWrapS(GLenum ws);
        void setWrapT(GLenum wt);
        void setMaxAnisotropy(GLfloat max_anisotropy);
        void setBorderColor(glm::vec4 border_color);
        void setSamplerParameters();
        Sampler(GLenum magnification_filter = GL_LINEAR, GLenum  minification_filter = GL_LINEAR_MIPMAP_LINEAR, GLenum wrap_s = GL_REPEAT, GLenum wrap_t = GL_REPEAT, glm::vec4 border_color = { 1,1,1,1 }, GLfloat max_anisotropy = 1.0f);
        void create();
        void destroy();


        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Sampler(Sampler const&) = delete;
        Sampler& operator=(Sampler const&) = delete;
    };
}




#endif