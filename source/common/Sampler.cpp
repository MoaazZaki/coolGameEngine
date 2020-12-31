#include "Sampler.hpp"

void famm::Sampler::bindSampler(GLuint unit)
{
    glBindSampler(unit, sampler);
}

void famm::Sampler::setMagnificationFilter(GLenum mf)
{
    magnification_filter = mf;
}

void famm::Sampler::setMinificationFilter(GLenum mf)
{
    minification_filter = mf;
}

void famm::Sampler::setWrapS(GLenum ws)
{
    wrap_s = ws;
}

void famm::Sampler::setWrapT(GLenum wt)
{
    wrap_t = wt;
}

void famm::Sampler::setMaxAnisotropy(GLfloat max_anisotropy)
{
    max_anisotropy = max_anisotropy;
}

void famm::Sampler::setBorderColor(glm::vec4 border_color)
{
    border_color = border_color;
}

void famm::Sampler::setSamplerParameters()
{
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap_s);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap_t);
    glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
}

famm::Sampler::Sampler(GLenum magnification_filter, GLenum  minification_filter , GLenum wrap_s, GLenum wrap_t, glm::vec4 border_color , GLfloat max_anisotropy)
{
    sampler = 0;

    this->magnification_filter = magnification_filter;
    this->minification_filter = minification_filter;
    this->wrap_s = wrap_s;
    this->wrap_t = wrap_t;
    this->border_color = border_color;
    this->max_anisotropy = max_anisotropy;
}
void famm::Sampler::create() {
    glGenSamplers(1, &sampler);
}

void famm::Sampler::destroy() {
    glDeleteSamplers(1, &sampler);
}