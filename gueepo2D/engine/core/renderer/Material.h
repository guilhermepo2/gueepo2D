// Material.h
// A Material is a structure that holds a shader and uniform values

#include "core/Common.h"
#include "core/containers/string.h"
#include "core/math/math.h"

namespace gueepo {
    class Texture;
    class Shader;

    class Material {
    public:
        Material(Shader* shader);

        virtual void Set(const gueepo::string& name, math::mat4 mat) const { unref(name, mat); }
        virtual void Set(const gueepo::string& name, float x, float y, float z, float w) const { unref(name, x, y, z, w); }
        virtual void Set(Texture* tex) const { unref(tex); }
        virtual void Set(Texture* tex, int index) const { unref(tex, index); }

        virtual void SetupTextureSamplerArray(const gueepo::string& name, int size) const { unref(name, size); }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        Shader* m_Shader;
        // #todo: store uniforms data, instead of just having functions to set them
        // #todo: store textures
        // #todo: flags
    };
}
