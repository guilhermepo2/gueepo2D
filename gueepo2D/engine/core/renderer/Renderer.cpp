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

	SpriteBatcher* Renderer::s_spriteBatcher = nullptr;
	SpriteBatcher* Renderer::s_uiBatcher;


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
		s_spriteBatcher = new SpriteBatcher();
		s_uiBatcher = new SpriteBatcher();

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

		s_spriteBatcher->Initialize(s_RendererAPI, shaderLibrary.Get("sprite shader"));
		s_uiBatcher->Initialize(s_RendererAPI, shaderLibrary.Get("font shader"));
	}

	void Renderer::Shutdown() {
		s_spriteBatcher->Shutdown();
		s_uiBatcher->Shutdown();

		delete s_spriteBatcher;
		delete s_uiBatcher;
	}

	void Renderer::Begin(const OrtographicCamera& camera) {
		s_RendererAPI->SetClearColor(
			camera.GetBackGroundColor().rgba[0],
			camera.GetBackGroundColor().rgba[1],
			camera.GetBackGroundColor().rgba[2],
			camera.GetBackGroundColor().rgba[3]
		);
		s_RendererAPI->Clear();
	}

	void Renderer::End() {
		// nothing?
	}

	/*
	void Renderer::Submit(VertexArray* vertexArray, Shader* shader) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_RenderData.ViewProjection);
		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}
	*/

	void Renderer::SetUnpackAlignment(int value) {
		s_RendererAPI->SetUnpackAlignment(value);
	}
}