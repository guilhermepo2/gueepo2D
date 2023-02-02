#pragma once
#include <stdint.h>

namespace gueepo {
	class OpenGLIndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		~OpenGLIndexBuffer();
		void Bind() const;
		void Unbind() const;
		uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_indexBufferID;
		uint32_t m_Count;
	};
}