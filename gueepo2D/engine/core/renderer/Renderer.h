#pragma once
#include "core/math/vec3.h"

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

		virtual void DrawIndexed(VertexArray* vertexArray) = 0;
		virtual void DrawIndexed(VertexArray* vertexArray, uint32_t count) = 0;

		static Renderer* GetRendererAPI();
		static API GetAPI() { return s_API; }

	private:
		static API s_API;

	protected:
		virtual void Clear() = 0;
		virtual void SetClearColor(const math::vec3& color) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetUnpackAlignment_Internal(int value) = 0;
	};
}