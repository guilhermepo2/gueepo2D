//
// OpenGLMaterial.h
//

#include "core/renderer/Material.h"

namespace gueepo {
	class OpenGLMaterial : public Material {
	public:
		OpenGLMaterial(Shader* shader) : Material(shader) {}
		~OpenGLMaterial();

		virtual void Set(const gueepo::string& name, math::mat4 mat) const;
		virtual void Set(const gueepo::string& name, float x, float y, float z, float w) const;
		virtual void Set(Texture* tex) const;
		virtual void Set(Texture* tex, int index) const;

		virtual void SetupTextureSamplerArray(const gueepo::string& name, int size);

		virtual void Bind() const;
		virtual void Unbind() const;
	};
}