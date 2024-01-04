#include "Target.h"
#include "platform/OpenGL/OpenGLTarget.h"

namespace gueepo {
    uint32_t Target::GetWidth() {
        return GetTexture()->GetWidth();
    }

    uint32_t Target::GetHeight() {
        return GetTexture()->GetHeight();
    }

    Target *Target::Create(int _width, int _height) {
        switch(Renderer::GetAPI()) {
            case Renderer::API::OpenGL: {
                return new OpenGLTarget(_width, _height);
            }
            case Renderer::API::DirectX:
            case Renderer::API::Metal:
            case Renderer::API::Vulkan:
            case Renderer::API::None:
                LOG_ERROR("API NOT SUPPORTED");
                return nullptr;
        }
    }
}

