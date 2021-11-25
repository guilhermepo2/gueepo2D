#pragma once
#include "core/renderer/BufferLayout.h"
#include "core/renderer/VertexBuffer.h"

namespace gueepo {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const override;
		void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout& GetLayout() override { return m_layout; }

	private:
		uint32_t m_vertexBufferID;
		BufferLayout m_layout;
	};
}