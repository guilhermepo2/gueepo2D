#include "gueepo2Dpch.h"
#include "Renderer.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/OrtographicCamera.h"

namespace gueepo {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	// #todo: BeginScene should receive and camera and any environment data
	void Renderer::BeginScene(OrtographicCamera& sceneCamera) {
		m_SceneData->ViewProjection = sceneCamera.GetViewProjectionMatrix();

		RenderCommand::SetClearColor(
			sceneCamera.GetBackGroundColor().rgba[0],
			sceneCamera.GetBackGroundColor().rgba[1],
			sceneCamera.GetBackGroundColor().rgba[2],
			sceneCamera.GetBackGroundColor().rgba[3]
		);
		RenderCommand::Clear();
	}

	void Renderer::EndScene() {}

	void Renderer::Submit(VertexArray* vertexArray, Shader* shader) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjection);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}