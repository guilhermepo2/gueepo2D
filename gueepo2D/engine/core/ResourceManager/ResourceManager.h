#pragma once
// =================================================================
// Resource Manager.h
// 
// The Resource Manager aims to... manage resources...
// =================================================================

namespace gueepo {

	class Texture;
	class Tilemap;

	class ResourceManager {
	public:
		ResourceManager() = default;
		~ResourceManager() = default;
		void ClearResources();
		void LoadFromFile(const std::string& path);

		void AddTexture(const std::string& textureId, const std::string& texturePath);
		Texture* GetTexture(const std::string& textureId);

		void AddTilemap(const std::string& tilemapId, const std::string& textureId);
		Tilemap* GetTilemap(const std::string& tilemapId);

	private:
		// #todo: use gueepo::string instead of std::string?
		// I can probably make use of the CRC hash to make the map and make things a bit better on runtime
		std::unordered_map<std::string, Texture*> m_textureResources;
		std::unordered_map<std::string, Tilemap*> m_tilemapResources;
	};
}