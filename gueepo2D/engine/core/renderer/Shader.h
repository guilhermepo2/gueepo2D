#pragma once
#include <string>
#include "core/math/mat4.h"
#include "core/containers/hashed_string.h"
#include <unordered_map>

namespace gueepo {
	
	class string;

	class Shader {
	public:
		virtual ~Shader() {}

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* CreateFromFile(const std::string& vertexFile, const std::string& fragmentFile);

		inline uint32_t GetShaderProgramID() const { return m_ShaderProgramID; }
	protected:
		uint32_t m_ShaderProgramID;
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