#pragma once
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/IndexBuffer.h"

namespace gueepo {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffer() const = 0;
		virtual const IndexBuffer* GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}