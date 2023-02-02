#pragma once
#include "core/containers/string.h"
#include "core/math/vec3.h"
#include "core/math/mat4.h"
#include <stdint.h>

namespace gueepo {

	class Color;
	class FontSprite;
	class OrtographicCamera;
	class Texture;
	class TextureRegion;

	class Renderer {
	public:

		enum class API {
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3,
			Metal = 4
		};

		static void Initialize();
		static void Shutdown();

		// Messages to the Renderer
		static void Clear(float r, float g, float b, float a);

		// AFAIK these two are OpenGL specific...
		static void SetUnpackAlignment(int value);

		static void BeginFrame(const OrtographicCamera& camera);
		static void EndFrame();

		static void Draw(Texture* texture);
		static void Draw(Texture* texture, int x, int y);
		static void Draw(Texture* texture, int x, int y, int w, int h);
		static void Draw(Texture* texture, int x, int y, int w, int h, Color color);

		static void Draw(TextureRegion* texture);
		static void Draw(TextureRegion* texture, int x, int y);
		static void Draw(TextureRegion* texture, int x, int y, int w, int h);
		static void Draw(TextureRegion* texture, int x, int y, int w, int h, Color color);

		static void Draw(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color);
		static void DrawString(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color);

		static std::string GraphicsContextString();
		

		static Renderer* GetRendererAPI();
		static API GetAPI() { return s_API; }

	private:
		static API s_API;

	protected:
		virtual void Clear() = 0;
		virtual void SetClearColor(const math::vec3& color) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		
		virtual void Initialize_Internal() = 0;
		virtual void Shutdown_Internal() = 0;
		virtual std::string GraphicsContextString_Internal() = 0;
		virtual void SetUnpackAlignment_Internal(int value) = 0;
		virtual void SetBufferData_Internal(const void* data, uint32_t size) = 0;

		// Effectively Drawing
		virtual void BeginFrame_Internal(const OrtographicCamera& camera) = 0;
		virtual void Draw_Internal(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color) = 0;
		virtual void DrawString_Internal(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) = 0;
		virtual void EndFrame_Internal() = 0;
	};
}