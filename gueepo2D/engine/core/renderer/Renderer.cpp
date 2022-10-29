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

		if (renderer_internal == nullptr) {
			LOG_ERROR("Error initializing Renderer API");
			return;
		}
	}

	void Renderer::Shutdown() {}

	void Renderer::Clear(float r, float g, float b, float a) {
		renderer_internal->SetClearColor(r,g,b,a);
		renderer_internal->Clear();
	}

	void Renderer::SetUnpackAlignment(int value) {
		renderer_internal->SetUnpackAlignment_Internal(value);
	}

	gueepo::Renderer* Renderer::GetRendererAPI() { return renderer_internal; }

}