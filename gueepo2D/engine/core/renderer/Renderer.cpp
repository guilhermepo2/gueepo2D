#include "gueepo2Dpch.h"
#include "Renderer.h"

#include "core/Containers/string.h"
#include "core/filesystem/Filesystem.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/Renderer/RendererAPI.h"
#include "core/Renderer/Shader.h"
#include "core/Renderer/SpriteBatcher.h"
	
// Specific Renderer APIs
#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace gueepo {

	static RendererAPI* s_RendererAPI = nullptr;

	static RendererAPI* InitRendererAPI() {
		
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			LOG_ERROR("RENDERER API 'NONE' NOT IMPLEMENTED!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLRendererAPI();
			break;
		case RendererAPI::API::DirectX:
		case RendererAPI::API::Vulkan:
		case RendererAPI::API::Metal:
			LOG_ERROR("RENDERER API NOT IMPLEMENTED!");
			break;
			
		}

		return nullptr;
	}
	
	// ========================================================================
	// ========================================================================

	void Renderer::Initialize() {
		
		s_RendererAPI = InitRendererAPI();

		if (s_RendererAPI == nullptr) {
			LOG_ERROR("Error initializing Renderer API");
			return;
		}
	}

	void Renderer::Shutdown() {}

	void Renderer::Clear(float r, float g, float b, float a) {
		s_RendererAPI->SetClearColor(r,g,b,a);
		s_RendererAPI->Clear();
	}

	// #todo: ehrm........ not sure if I want this
	RendererAPI* Renderer::GetRendererAPI() { return s_RendererAPI; }

	void Renderer::SetUnpackAlignment(int value) {
		s_RendererAPI->SetUnpackAlignment(value);
	}
}