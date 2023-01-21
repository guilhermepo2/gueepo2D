#pragma once
#include "core/math/vec3.h"
#include "core/math/mat4.h"
#include <stdint.h>

namespace gueepo {

	class OrtographicCamera;
	class Shader;
	class SpriteBatcher;
	class VertexArray;

	class Renderer {
	public:

		enum class API {
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3,
			Metal = 4
		};

		static void Initialize();
		static void Shutdown();
		static void Clear(float r, float g, float b, float a);
		static void SetUnpackAlignment(int value);
		static void SetBufferData(const void* data, uint32_t size);

		static void DrawIndexed(math::mat4 viewProjectionMatrix);
		static void DrawIndexed(math::mat4 viewProjectionMatrix, uint32_t count);
		static std::string GraphicsContextString();
		

		static Renderer* GetRendererAPI();
		static API GetAPI() { return s_API; }

	private:
		static API s_API;

	protected:
		virtual void Clear() = 0;
		virtual void SetClearColor(const math::vec3& color) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		
		virtual void Initialize_Internal() = 0;
		virtual void DrawIndexed_Internal(math::mat4 viewProjectionMatrix) = 0;
		virtual void DrawIndexed_Internal(math::mat4 viewProjectionMatrix, uint32_t count) = 0;
		virtual std::string GraphicsContextString_Internal() = 0;
		virtual void SetUnpackAlignment_Internal(int value) = 0;
		virtual void SetBufferData_Internal(const void* data, uint32_t size) = 0;
	};
}