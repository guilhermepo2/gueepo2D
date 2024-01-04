#include "OpenGLTarget.h"
#include <glad/glad.h>

namespace gueepo {

    OpenGLTarget::OpenGLTarget(uint32_t _width, uint32_t _height) {
        m_width = _width;
        m_height = _height;
        glGenFramebuffers(1, &m_framebufferId);

        glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

        m_texture = Texture::Create(m_width, m_height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->GetTextureID(), 0);
    }

    OpenGLTarget::~OpenGLTarget() {
        if(m_framebufferId > 0) {
            glDeleteFramebuffers(1, &m_framebufferId);
            m_framebufferId = 0;
        }
    }

    Texture *OpenGLTarget::GetTexture() {
        return m_texture;
    }

    void OpenGLTarget::Clear(gueepo::Color _color) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);
        glClearColor(_color.rgba[0], _color.rgba[1], _color.rgba[2], _color.rgba[3]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}