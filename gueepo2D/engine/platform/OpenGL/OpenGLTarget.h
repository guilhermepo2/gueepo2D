#pragma once
#include "core/renderer/Target.h"

namespace gueepo {
    class OpenGLTarget : public Target {
    public:
        OpenGLTarget(uint32_t _width, uint32_t _height);
        ~OpenGLTarget();

        virtual Texture* GetTexture();
        virtual void Clear(gueepo::Color _color);

    protected:
        unsigned int m_framebufferId;
        uint32_t m_width, m_height;
        Texture* m_texture;
    };
}