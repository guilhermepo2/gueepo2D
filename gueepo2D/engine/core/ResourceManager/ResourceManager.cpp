// =================================================================
// Resource Manager.h
// 
// The Resource Manager aims to... manage resources...
// =================================================================

#include "gueepo2Dpch.h"
#include "ResourceManager.h"

#include "core/renderer/Texture.h"
#include "utils/Tilemap.h"

namespace gueepo {

	void ResourceManager::ClearResources() {
		// have to free all the textures!
		for (auto textureEntry : m_textureResources) {
			delete textureEntry.second;
		}

		m_textureResources.clear();
	}

	void ResourceManager::AddTexture(const std::string& textureId, const std::string& texturePath) {
		Texture* texture = nullptr;
		texture = Texture::Create(texturePath);

		if (texture == nullptr) {
			LOG_ERROR("couldn't create texture {0}/{1}", textureId, texturePath);
			return;
		}

		m_textureResources.emplace(textureId, texture);
	}

	gueepo::Texture* ResourceManager::GetTexture(const std::string& textureId) {
		if (m_textureResources.find(textureId) != m_textureResources.end()) {
			return m_textureResources[textureId];
		}

		return nullptr;
	}

	void ResourceManager::AddTilemap(const std::string& tilemapId, const std::string& textureId) {
		Tilemap* tilemap = nullptr;
		
		if (m_textureResources.find(textureId) == m_textureResources.end()) {
			LOG_ERROR("error trying to create tilemap, texture {0} does not exist!", textureId);
			return;
		}

		Texture* texture = m_textureResources[textureId];
		tilemap = Tilemap::Create(texture);

		if (tilemap == nullptr) {
			LOG_ERROR("couldn't create tilemap {0}/{1}", tilemapId, textureId);
			return;
		}

		m_tilemapResources.emplace(tilemapId, tilemap);
	}

	gueepo::Tilemap* ResourceManager::GetTilemap(const std::string& tilemapId) {
		if (m_tilemapResources.find(tilemapId) != m_tilemapResources.end()) {
			return m_tilemapResources[tilemapId];
		}

		return nullptr;
	}
}