#include "gueepo2Dpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
#include "core/renderer/BufferLayout.h"

namespace gueepo {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::None:
		default:
			return 0;
			break;

		}
	}


	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_vertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_vertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer) {
		g2dassert(vertexBuffer->GetLayout().GetElements().size(), "vertex buffer has no layout!");

		glBindVertexArray(m_vertexArrayID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer) {
		glBindVertexArray(m_vertexArrayID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}