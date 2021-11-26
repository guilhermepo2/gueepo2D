#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"

namespace gueepo {
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(VertexArray* vertexArray);
		// static void Flush();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}