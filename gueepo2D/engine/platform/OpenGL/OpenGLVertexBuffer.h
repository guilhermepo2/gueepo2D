#pragma once
#include "core/renderer/BufferLayout.h"

namespace gueepo {
	class OpenGLVertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();
		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, uint32_t size);

		void SetLayout(const BufferLayout& layout) { m_layout = layout; }
		const BufferLayout& GetLayout() { return m_layout; }

	private:
		uint32_t m_vertexBufferID;
		BufferLayout m_layout;
	};
}