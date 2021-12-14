#include "gueepo2Dpch.h"
#include "SpriteComponent.h"
#include "core/renderer/BufferLayout.h"

static float spriteVertices[5 * 4] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
};

static unsigned int spriteIndices[6] = { 0, 1, 2, 2, 3, 0 };

namespace gueepo {
	Shader* SpriteComponent::defaultSpriteShader = nullptr;
	VertexArray* SpriteComponent::defaultVertexArray = nullptr;

	void SpriteComponent::InitializeDefaults() {
		if (defaultSpriteShader != nullptr && defaultVertexArray != nullptr) {
			LOG_WARN("default shader and vertex array are already initializing, backing");
			return;
		}

		defaultVertexArray = VertexArray::Create();
		VertexBuffer* squareVB = VertexBuffer::Create(spriteVertices, sizeof(spriteVertices));

		// #todo: I don't really like this, but since we are creating the shader and vertex array at the same time
		// this is maybe possibly not totally bad?
		// maybe I should work with the idea of Materials, and materials have their own shaders, buffer layouts, uniforms, whatever
		// and then I can just have a "Default Sprite Material"
		{
			gueepo::BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float2, "a_TexCoord"}
			};
			squareVB->SetLayout(layout);
		}
		defaultVertexArray->AddVertexBuffer(squareVB);


		gueepo::IndexBuffer* sq_IndexBuffer = gueepo::IndexBuffer::Create(spriteIndices, 6);
		defaultVertexArray->SetIndexBuffer(sq_IndexBuffer);
		defaultVertexArray->Unbind();

		// #todo: well, ideally we should have a default assets folder or some way that we know this is not going to break, lmao.
		defaultSpriteShader = Shader::CreateFromFile("./assets/shaders/sprite.vertex", "./assets/shaders/sprite.fragment");
	}

}