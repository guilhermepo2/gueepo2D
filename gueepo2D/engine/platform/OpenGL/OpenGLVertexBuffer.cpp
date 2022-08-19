#include "gueepo2Dpch.h"
#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace gueepo {

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
		glGenBuffers(1, &m_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		glGenBuffers(1, &m_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_vertexBufferID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

}