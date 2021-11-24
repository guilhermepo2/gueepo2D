#pragma once
#include "core/renderer/IndexBuffer.h"

namespace gueepo {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();
		void Bind() const;
		void Unbind() const;
		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_indexBufferID;
		uint32_t m_Count;
	};
}