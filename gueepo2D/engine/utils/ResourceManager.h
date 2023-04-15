//
// ResourceManager.h
// @description stores a map for varied types of data.
//

#pragma once
#include <map>
#include <gueepo2d.h>

namespace gueepo {
	class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		void ClearResources();

		void AddTexture(std::string textureId, Texture* tex);
		void AddTexture(std::string textureId, std::string filepath);
		Texture* GetTexture(std::string textureId);
		bool ContainsTexture(std::string textureId);

		void AddTextureRegion(std::string textureRegionId, TextureRegion* tex);
		TextureRegion* GetTextureRegion(std::string textureRegionId);

		void AddFontSprite(gueepo::string fontSpriteId, gueepo::FontSprite* fontSprite);
		void AddFontSprite(gueepo::string fontSpriteId, int fontSize, std::string filepath);
		FontSprite* GetFontSprite(std::string fontSpriteId);

	private:
		std::map<std::string, Texture*> m_textures;
		std::map<std::string, TextureRegion*> m_textureRegions;
		std::map<std::string, Font*> m_fontFiles;
		std::map<std::string, FontSprite*> m_fontSprites;
		// todo: scenes? ui files? sounds?
	};
}
