#pragma once
#include "core/renderer/VertexBuffer.h"

namespace gueepo {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_vertexBufferID;
	};
}