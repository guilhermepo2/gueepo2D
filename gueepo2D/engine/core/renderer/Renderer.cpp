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
	static ShaderLibrary shaderLibrary;

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

		// #todo: well, ideally we should have a default assets folder or some way that we know this is not going to break, lmao.
		// I think it makes sense that the renderer itself handles the shaders, not the batches...
		LOG_INFO("Verifying shaders folder...");
		bool bShaderPathExists = gueepo::filesystem::DirectoryExists("./assets/shaders");

		if (bShaderPathExists) {
			shaderLibrary.Load("sprite shader", "./assets/shaders/sprite.vertex", "./assets/shaders/sprite.fragment");
			shaderLibrary.Load("font shader", "./assets/shaders/font.vertex", "./assets/shaders/font.fragment");
		}
		else {
			LOG_ERROR("couldn't find path assets/shaders");
			LOG_ERROR("there might be issues with the renderer!");
			return;
		}
	}

	void Renderer::Shutdown() {}

	void Renderer::Clear(float r, float g, float b, float a) {
		s_RendererAPI->SetClearColor(r,g,b,a);
		s_RendererAPI->Clear();
	}

	// #todo: ehrm........ not sure if I want this
	Shader* Renderer::GetShader(const std::string & shaderName) { return shaderLibrary.Get(shaderName.c_str()); }
	RendererAPI* Renderer::GetRendererAPI() { return s_RendererAPI; }

	void Renderer::SetUnpackAlignment(int value) {
		s_RendererAPI->SetUnpackAlignment(value);
	}
}