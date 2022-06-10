#pragma once
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "OrtographicCamera.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "core/Containers/string.h"

namespace gueepo {

	class OrtographicCamera;
	class Texture;
	class FontSprite;

	class Renderer {
	public:

		static void Initialize();
		static void Shutdown();

		static int GetDrawCalls();

		static void BeginScene(OrtographicCamera& sceneCamera);
		static void EndScene();
		static void Submit(VertexArray* vertexArray, Shader* shader);

		static void SetUnpackAlignment(int value);

		static void Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture, Color color);
		static void Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture);
		static void Draw(const math::mat4& transform, Texture* texture);
		static void Draw(const math::vec2& position, Texture* texture);
		static void Draw(Texture* texture); // hey... I don't know why you would ask us to just draw a texture, but hey, you have the option!
		static void DrawText(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color);

		static void Flush();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static void StartBatch();
		static void NextBatch();
		
	};
}