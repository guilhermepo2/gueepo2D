#pragma once
#include<vector>
#include "core/Log.h"

namespace gueepo {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t GetShaderDataSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return 2 * sizeof(float);
		case ShaderDataType::Float3:	return 3 * sizeof(float);
		case ShaderDataType::Float4:	return 4 * sizeof(float);
		case ShaderDataType::Mat3:		return 3 * 3 * sizeof(float);
		case ShaderDataType::Mat4:		return 4 * 4 * sizeof(float);
		case ShaderDataType::Int:		return sizeof(int);
		case ShaderDataType::Int2:		return 2 * sizeof(int);
		case ShaderDataType::Int3:		return 3 * sizeof(int);
		case ShaderDataType::Int4:		return 4 * sizeof(int);
		case ShaderDataType::Bool:		return sizeof(bool);
		}

		LOG_ERROR("UNKNOWN SHADER DATA TYPE: {0}", type);
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(GetShaderDataSize(type)), Offset(0), Normalized(normalized) {

		}

		uint32_t GetCount() const {
			switch (Type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}

			LOG_ERROR("UNKNOWN SHADER DATA TYPE: {0}", Type);
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& element)
		: m_BufferElements(element) {
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }
		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }

	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_BufferElements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride = 0;
	};
}