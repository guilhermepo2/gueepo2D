#pragma once
#include <vector>

namespace gueepo {

	class OpenGLVertexBuffer;
	class OpenGLIndexBuffer;

	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const;
		void Unbind() const;
		void AddVertexBuffer(OpenGLVertexBuffer* vertexBuffer);
		void SetIndexBuffer(OpenGLIndexBuffer* indexBuffer);

		const std::vector<OpenGLVertexBuffer*>& GetVertexBuffer() const { return m_VertexBuffers; }
		const OpenGLIndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_vertexArrayID;
		std::vector<OpenGLVertexBuffer*> m_VertexBuffers;
		OpenGLIndexBuffer* m_IndexBuffer;
	};
}