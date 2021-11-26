#include "gueepo2Dpch.h"
#include "Renderer.h"
#include "core/renderer/VertexArray.h"

namespace gueepo {

	// #todo: BeginScene should receive and camera and any environment data
	void Renderer::BeginScene() {}
	void Renderer::EndScene() {}

	void Renderer::Submit(VertexArray* vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}