#include "gueepo2Dpch.h"
#include "Renderer.h"

#include "core/Containers/string.h"
#include "core/filesystem/Filesystem.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/Shader.h"
#include "core/renderer/SpriteBatcher.h"
	
// Specific Renderer APIs
#include "platform/OpenGL/OpenGLRenderer.h"

namespace gueepo {

	Renderer::API Renderer::s_API = Renderer::API::OpenGL;
	Renderer* renderer_internal;

	static Renderer* InitRendererAPI() {
		
		switch (Renderer::GetAPI()) {
		case Renderer::API::None:
			LOG_ERROR("RENDERER API 'NONE' NOT IMPLEMENTED!");
			break;
		case Renderer::API::OpenGL:
			return new OpenGLRenderer();
			break;
		case Renderer::API::DirectX:
		case Renderer::API::Vulkan:
		case Renderer::API::Metal:
			LOG_ERROR("RENDERER API NOT IMPLEMENTED!");
			break;
			
		}

		return nullptr;
	}
	
	// ========================================================================
	// ========================================================================

	void Renderer::Initialize() {
		
		renderer_internal = InitRendererAPI();

		g2dassert(renderer_internal != nullptr, "error initializing renderer API!");

		renderer_internal->Initialize_Internal();

	}

	void Renderer::Shutdown() {}

	void Renderer::Clear(float r, float g, float b, float a) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");

		renderer_internal->SetClearColor(r,g,b,a);
		renderer_internal->Clear();
	}

	void Renderer::DrawIndexed(VertexArray* vertexArray) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");

		renderer_internal->DrawIndexed_Internal(vertexArray);
	}

	void Renderer::DrawIndexed(VertexArray* vertexArray, uint32_t count) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");

		renderer_internal->DrawIndexed_Internal(vertexArray, count);
	}

	std::string Renderer::GraphicsContextString() {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");

		return renderer_internal->GraphicsContextString_Internal();
	}

	void Renderer::SetUnpackAlignment(int value) {
		renderer_internal->SetUnpackAlignment_Internal(value);
	}

	gueepo::Renderer* Renderer::GetRendererAPI() { return renderer_internal; }

}