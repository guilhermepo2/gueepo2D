#pragma once
#include <string>
#include "core/math/mat4.h"
#include "core/Containers/hashed_string.h"

namespace gueepo {
	
	class string;

	class Shader {
	public:
		virtual ~Shader() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetMat4(const std::string& name, math::mat4 mat) const = 0;
		virtual void SetVec4(const std::string& name, float x, float y, float z, float w) const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* CreateFromFile(const std::string& vertexFile, const std::string& fragmentFile);
	};

	class ShaderLibrary {
	public:
		void Add(const gueepo::hashed_string& name, Shader* shader);
		Shader* Load(const gueepo::hashed_string& name, const gueepo::string& vertex, const gueepo::string& fragment);
		Shader* Get(const gueepo::hashed_string& name);
		bool Exists(gueepo::hashed_string name) const;
	private:
		std::unordered_map<gueepo::hashed_string, Shader*, StringHasher> m_Shaders;
	};
}