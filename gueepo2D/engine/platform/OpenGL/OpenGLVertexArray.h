#pragma once
#include "core/renderer/VertexArray.h"

namespace gueepo {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
		void SetIndexBuffer(IndexBuffer* indexBuffer) override;

		const std::vector<VertexBuffer*>& GetVertexBuffer() const override { return m_VertexBuffers; }
		const IndexBuffer* GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_vertexArrayID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}