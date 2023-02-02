#include "Renderer.h"

#include "core/Log.h"
#include "core/filesystem/Filesystem.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/Texture.h"
#include "utils/TextureRegion.h"
	
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

	void Renderer::Shutdown() {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");
		renderer_internal->Shutdown_Internal();
	}

	void Renderer::Clear(float r, float g, float b, float a) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");

		renderer_internal->SetClearColor(r,g,b,a);
		renderer_internal->Clear();
	}

	// ==========================================================================
	// Drawing
	// ==========================================================================
	void Renderer::BeginFrame(const OrtographicCamera& camera) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");
		renderer_internal->BeginFrame_Internal(camera);
	}

	void Renderer::EndFrame() {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");
		renderer_internal->EndFrame_Internal();
	}

	void Renderer::Draw(Texture* texture) { Draw(texture, 0, 0); }
	void Renderer::Draw(Texture* texture, int x, int y) { Draw(texture, x, y, static_cast<int>(texture->GetWidth()), static_cast<int>(texture->GetHeight())); }
	void Renderer::Draw(Texture* texture, int x, int y, int w, int h) { Draw(texture, x, y, w, h, Color(1.0f, 1.0f, 1.0f, 1.0f)); }

	void Renderer::Draw(Texture* texture, int x, int y, int w, int h, Color color) {
		math::vec2 scale(static_cast<float>(w), static_cast<float>(h));
		math::vec2 position(x, y);
		math::mat4 transformMatrix = math::mat4::CreateScale(scale) * math::mat4::CreateTranslation(position);
		Draw(texture, transformMatrix, math::vec2::Zero, math::vec2::One, color);
	}

	void Renderer::Draw(TextureRegion* texture) { Draw(texture, 0, 0); }
	void Renderer::Draw(TextureRegion* texture, int x, int y) { Draw(texture, x, y, texture->GetTexture()->GetWidth(), texture->GetTexture()->GetHeight()); }
	void Renderer::Draw(TextureRegion* texture, int x, int y, int w, int h) { Draw(texture, x, y, w, h, Color(1.0f, 1.0f, 1.0f, 1.0f)); }
	void Renderer::Draw(TextureRegion* texture, int x, int y, int w, int h, Color color) {
		Texture* tex = texture->GetTexture();
		math::vec2 scale(w, h);
		math::vec2 position(x, y);
		math::mat4 transformMatrix = math::mat4::CreateScale(scale) * math::mat4::CreateTranslation(position);

		math::rect coords = texture->GetCoordinates();
		Draw(tex, transformMatrix, coords.bottomLeft, coords.topRight, color);
	}

	void Renderer::Draw(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");
		renderer_internal->Draw_Internal(texture, transform, texCoordMin, texCoordMax, color);
	}

	void Renderer::DrawString(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) {
		assert(renderer_internal != nullptr, "renderer wasn't initialized!");
		renderer_internal->DrawString(fontSprite, text, position, scale, color);
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