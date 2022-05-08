// =================================================================
// Resource Manager.h
// 
// The Resource Manager aims to... manage resources...
// =================================================================

#include "gueepo2Dpch.h"
#include "ResourceManager.h"

#include "core/filesystem/json.h"
#include "core/renderer/Texture.h"
#include "utils/Tilemap.h"

namespace gueepo {

	void ResourceManager::ClearResources() {
		// have to free all the textures!
		for (auto textureEntry : m_textureResources) {
			delete textureEntry.second;
		}

		m_textureResources.clear();

		for (auto tilemapEntry : m_tilemapResources) {
			delete tilemapEntry.second;
		}
		m_tilemapResources.clear();
	}

	void ResourceManager::LoadFromFile(const std::string& path) {
		ClearResources();
		gueepo::json resourceFile(path);

		if (!resourceFile.IsValid()) {
			LOG_ERROR("couldn't load resource file: {0}", path);
			return;
		}

		// 1. get textures object
		std::vector<gueepo::json> textures;
		if (resourceFile.GetArray("textures", textures)) {
			for (int i = 0; i < textures.size(); i++) {
				std::string id;
				std::string path;
				bool bId = textures[i].GetString("id", id);
				bool bPath = textures[i].GetString("path", path);
				
				if (bId && bPath) {
					AddTexture(id, path);
				}
			}
		}

		// 2. get tilemaps object
		std::vector<gueepo::json> tilemaps;
		if (resourceFile.GetArray("tilemaps", tilemaps)) {
			for (int i = 0; i < tilemaps.size(); i++) {
				std::string id;
				std::string texture;
				bool bId = tilemaps[i].GetString("id", id);
				bool bTexture = tilemaps[i].GetString("texture", texture);

				if (bId && bTexture) {
					AddTilemap(id, texture);
				}

				// trying to slice
				Tilemap* tilemap = GetTilemap(id);
				int slice_width;
				int slice_height;
				bool bsliceW = tilemaps[i].GetInt("slice_width", slice_width);
				bool bsliceH = tilemaps[i].GetInt("slice_height", slice_height);
				if (bsliceW && bsliceH && tilemap != nullptr) {
					tilemap->Slice(slice_width, slice_height);
				}
			}
		}
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

		LOG_ERROR("couldn't find tilemap resource: {0}", tilemapId);
		return nullptr;
	}
}