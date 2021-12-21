#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "OrtographicCamera.h"

namespace gueepo {

	class OrtographicCamera;
	class Texture;

	class Renderer {
	public:

		static void Initialize();
		static void Shutdown();

		static void BeginScene(OrtographicCamera& sceneCamera);
		static void EndScene();
		static void Submit(VertexArray* vertexArray, Shader* shader);
		static void Draw(const math::Matrix4& transform, Texture* texture);
		static void Flush();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	protected:
		
	};
}