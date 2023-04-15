#include "ResourceManager.h"

namespace gueepo {

	ResourceManager::ResourceManager() {}

	ResourceManager::~ResourceManager(){
		ClearResources();
	}

	void ResourceManager::ClearResources() {
		for (auto texture : m_textures) {
			delete texture.second;
		}
		m_textures.clear();

		for (auto textureRegion : m_textureRegions) {
			delete textureRegion.second;
		}
		m_textureRegions.clear();

		for (auto fontFile : m_fontFiles) {
			delete fontFile.second;
		}
		m_fontFiles.clear();

		for (auto fontSprite : m_fontSprites) {
			delete fontSprite.second;
		}
		m_fontSprites.clear();
	}

	// ************************************************************************
	void ResourceManager::AddTexture(std::string textureId, Texture* tex) {
		m_textures.emplace(textureId, tex);
	}

	// ************************************************************************
	void ResourceManager::AddTexture(std::string textureId, std::string filepath) {
		Texture* tex = Texture::Create(filepath);

		if (tex != nullptr) {
			AddTexture(textureId, tex);
		}
	}

	// ************************************************************************
	Texture* ResourceManager::GetTexture(std::string textureId) {
		Texture* tex = nullptr;

		if (m_textures.count(textureId) != 0) {
			tex = m_textures[textureId];
		}

		return tex;
	}

	// ************************************************************************
	bool ResourceManager::ContainsTexture(std::string textureId) {
		return m_textures.count(textureId) != 0;
	}

	// ************************************************************************
	void ResourceManager::AddTextureRegion(std::string textureRegionId, TextureRegion* tex) {
		m_textureRegions.emplace(textureRegionId, tex);
	}

	// ************************************************************************
	TextureRegion* ResourceManager::GetTextureRegion(std::string textureRegionId) {
		TextureRegion* tex = nullptr;

		if (m_textureRegions.count(textureRegionId) != 0) {
			tex = m_textureRegions[textureRegionId];
		}

		return tex;
	}

	// ************************************************************************
	void ResourceManager::AddFontSprite(gueepo::string fontSpriteId, gueepo::FontSprite* fontSprite) {
		m_fontSprites.emplace(fontSpriteId, fontSprite);
	}

	// ************************************************************************
	void ResourceManager::AddFontSprite(gueepo::string fontSpriteId, int fontSize, std::string filepath){
		Font* fontFile = nullptr;

		if (m_fontFiles.count(filepath.c_str()) != 0) {
			fontFile = m_fontFiles[filepath];
		}
		else {
			fontFile = Font::CreateNewFont(filepath);
			m_fontFiles.emplace(filepath, fontFile);
		}

		if (fontFile != nullptr) {
			FontSprite* fontSprite = new FontSprite(fontFile, fontSize);

			if (fontSprite != nullptr) {
				fontSprite->SetLineGap(fontSize);
				AddFontSprite(fontSpriteId, fontSprite);
			}
		}
	}

	// ************************************************************************
	gueepo::FontSprite* ResourceManager::GetFontSprite(std::string fontSpriteId) {
		FontSprite* fontSprite = nullptr;

		if (m_fontSprites.count(fontSpriteId) != 0) {
			fontSprite = m_fontSprites[fontSpriteId];
		}

		return fontSprite;

	}

}
