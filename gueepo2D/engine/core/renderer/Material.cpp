#include "Material.h"

#include "core/Log.h"

namespace gueepo {
	Material::Material(Shader* shader) : m_Shader(shader) {}

	void Material::SetTextureToIndex(Texture* tex, int index) {
		g2dassert(m_Textures != nullptr, "texture array is not initialized!");
		g2dassert(index <= m_maxTextures, "trying to set more textures than the maximum!");

		m_Textures[index] = tex;
	}

	gueepo::Texture* Material::GetTextureOnIndex(int index) {
		g2dassert(m_Textures != nullptr, "texture array is not initialized!");
		g2dassert(index <= m_maxTextures, "trying to set more textures than the maximum!");
		
		return m_Textures[index];
	}

	void Material::ClearTextures() {
		g2dassert(m_Textures != nullptr, "texture array is not initialized!");
		for (int i = 0; i < m_maxTextures; i++) {
			m_Textures[i] = nullptr;
		}
	}

}
