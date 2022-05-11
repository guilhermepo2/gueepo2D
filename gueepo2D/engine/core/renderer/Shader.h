#pragma once
#include <string>
#include "core/math/mat4.h"

namespace gueepo {
	class Shader {
	public:
		virtual ~Shader() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetMat4(const std::string& name, math::mat4 mat) const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* CreateFromFile(const std::string& vertexFile, const std::string& fragmentFile);
	};
}