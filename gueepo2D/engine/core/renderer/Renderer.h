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

	class Renderer {
	public:
		static void BeginScene(OrtographicCamera& sceneCamera);
		static void EndScene();
		static void Submit(VertexArray* vertexArray, Shader* shader);
		// static void Flush();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	protected:
		struct SceneData {
			math::Matrix4 ViewProjection;
		};

		static SceneData* m_SceneData;
	};
}