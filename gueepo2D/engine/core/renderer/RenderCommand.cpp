#include "gueepo2Dpch.h"
#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace gueepo {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}