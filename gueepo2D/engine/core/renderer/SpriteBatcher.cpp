#include "gueepo2Dpch.h"
#include "SpriteBatcher.h"

#include "core/Log.h"
#include "core/Containers/string.h"
#include "core/filesystem/Filesystem.h"
#include "core/math/math.h"
#include "core/renderer/BufferLayout.h"
#include "core/renderer/FontSprite.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/Texture.h"

#include "utils/TextureRegion.h"



namespace gueepo {
	// ------------------------------------------------------
	void SpriteBatcher::Initialize() {

		LOG_INFO("quad vertex size: {0}", sizeof(QuadVertex));
		LOG_INFO("sizeof color class: {0}", sizeof(Color));

		m_renderData.quadVertexBase = new QuadVertex[m_renderData.MaxVertices];

		m_renderData.quadVertexPosition[0] = { -0.5f, -0.5f, 0.0f };
		m_renderData.quadVertexPosition[1] = { 0.5f, -0.5f, 0.0f };
		m_renderData.quadVertexPosition[2] = { 0.5f,  0.5f, 0.0f };
		m_renderData.quadVertexPosition[3] = { -0.5f,  0.5f, 0.0f };
		
		m_isInitialized = true;
	}

	// ------------------------------------------------------
	void SpriteBatcher::Shutdown() {
		delete[] m_renderData.quadVertexBase;
	}

	// ------------------------------------------------------
	void SpriteBatcher::Begin(const OrtographicCamera& camera) {
		m_renderData.ViewProjection = camera.GetViewProjectionMatrix();
		m_renderData.RenderStats.DrawCalls = 0;
		StartBatch();
	}

	// ------------------------------------------------------
	void SpriteBatcher::End() {
		Flush();
	}

	// ------------------------------------------------------
	// Drawing Textures
	// ------------------------------------------------------
	void SpriteBatcher::Draw(Texture* texture, const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Color color, float shaderType /* = 1 */) {

		g2dassert(m_isInitialized, "trying to draw without initializing the sprite batcher?!");

		if (
			m_renderData.quadIndexCount >= m_renderData.MaxIndices ||
			m_renderData.TextureSlotIndex >= m_renderData.MaxTextureSlots
			) {
			NextBatch();
		}

		float textureSlot = -1.0f;

		// searching for the texture on the array
		for (size_t i = 0; i < m_renderData.TextureSlotIndex; i++) {
			if (m_renderData.TextureSlots[i] == texture) {
				textureSlot = (float)i;
				break;
			}
		}

		// if we didn't find it, we add it.
		if (textureSlot == -1.0f) {
			// #todo: check if we are not over the maximum texture slots, if we are we have to flush
			textureSlot = (float)m_renderData.TextureSlotIndex;
			m_renderData.TextureSlots[m_renderData.TextureSlotIndex] = texture;
			m_renderData.TextureSlotIndex++;
		}

		size_t quadVertexCount = 4;

		math::vec2 textureCoords[] = {
			{ textureCoordMin.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMax.y },
			{ textureCoordMin.x, textureCoordMax.y }
		};

		for (size_t i = 0; i < quadVertexCount; i++) {
			m_renderData.quadVertexPtrPosition->Position = transform * m_renderData.quadVertexPosition[i];
			m_renderData.quadVertexPtrPosition->TexCoord = textureCoords[i];
			m_renderData.quadVertexPtrPosition->TextureSlot = textureSlot;
			m_renderData.quadVertexPtrPosition->color = color;
			m_renderData.quadVertexPtrPosition->shaderType = shaderType;
			m_renderData.quadVertexPtrPosition++;
		}

		m_renderData.quadIndexCount += 6;
	}

	void SpriteBatcher::Draw(Texture* texture, const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax) {
		Draw(texture, transform, textureCoordMin, textureCoordMax, Color(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void SpriteBatcher::Draw(Texture* texture, const math::vec2& position, const math::vec2& scale) {
		math::mat4 transformMatrix = math::mat4::CreateScale(math::vec2(static_cast<float>(scale.x), static_cast<float>(scale.y))) * math::mat4::CreateTranslation(position);
		Draw(texture, transformMatrix * math::mat4::m4Identity, math::vec2::Zero, math::vec2::One);
	}

	void SpriteBatcher::Draw(Texture* texture, int x, int y, int w, int h) {
		Draw(texture, math::vec2(x, y), math::vec2(w, h));
	}

	void SpriteBatcher::Draw(Texture* texture, int x, int y) {
		Draw(texture, math::vec2(x, y), math::vec2((int)texture->GetWidth(), (int)texture->GetHeight()));
	}

	void SpriteBatcher::Draw(Texture* texture) {
		Draw(
			texture, 
			math::vec2::Zero, 
			math::vec2(
				static_cast<float>(texture->GetWidth()),
				static_cast<float>(texture->GetHeight())
			)
		);
	}

	// ------------------------------------------------------
	// Drawing Texture Regions
	// ------------------------------------------------------
	void SpriteBatcher::Draw(TextureRegion* texRegion, int x, int y, int w, int h, Color color) {
		Texture* t = texRegion->GetTexture();
		math::mat4 transformMatrix = 
			math::mat4::CreateScale(math::vec2(static_cast<float>(w), static_cast<float>(h))) * 
			math::mat4::CreateTranslation(math::vec2(x, y)
		);

		math::rect coords = texRegion->GetCoordinates();
		Draw(t, transformMatrix, coords.bottomLeft, coords.topRight, color);
	}

	void SpriteBatcher::Draw(TextureRegion* texRegion, int x, int y, int w, int h) {
		Draw(texRegion, x, y, w, h, Color(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void SpriteBatcher::Draw(TextureRegion* texRegion, int x, int y) {
		Draw(texRegion, x, y, texRegion->GetTexture()->GetWidth(), texRegion->GetTexture()->GetHeight());
	}

	// ------------------------------------------------------
	// Drawing Text
	// ------------------------------------------------------
	void SpriteBatcher::DrawString(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) {

		math::vec2 offset = math::vec2(0, 0);
		uint32_t last = 0;

		for (int i = 0, l = text.length(); i < l; i += text.utf8_length(i)) {
			uint32_t next = text.utf8_at(i);

			if (next == '\n') {
				offset.x = 0;
				offset.y += fontSprite->lineHeight(); // adding here because down there we are going to reverse it
				last = 0;
				continue;
			}

			const SpriteCharacter& ch = fontSprite->GetSpriteCharacter(next);
			if (ch.texture != nullptr) {
				math::vec2 at = offset + ch.bearing;
				at.x += ch.size.x / 2.0f;
				at.y += ch.size.y / 2.0f;

				if (i > 0 && text[i - 1] != '\n') {
					at.x += fontSprite->kerning(last, next);
				}

				// WE HAVE TO DO -AT.Y HERE BECAUSE WE DO -SCALE DOWN THERE
				// BECAUSE IN THE ORIGINAL FONT/TEXTURE, THE CHARACTERS ARE UPSIDE DOWN
				// SO THE BEARING AND OFFSET ARE FOR THAT OCCASION
				// SO BECAUSE WE INVERSING THE SCALE, WE HAVE TO INVERSE THE BEARING/OFFSET AS WELL!!
				at.y = -at.y;

				math::mat4 transformMatrix =
					math::mat4::CreateScale(ch.size) *
					math::mat4::CreateScale(math::vec2(scale, -scale)) *
					math::mat4::CreateTranslation(position + math::vec2(at.x, at.y));

				Draw(ch.texture, transformMatrix, math::vec2::Zero, math::vec2::One, color, 2.0f);
			}

			offset.x += ch.advance;
			last = next;
		}
	}

	int SpriteBatcher::GetDrawCalls() {
		return m_renderData.RenderStats.DrawCalls;
	}

	// ---------------------------------------------------------
	// Private Members
	// ---------------------------------------------------------
	void SpriteBatcher::StartBatch() {
		m_renderData.TextureSlotIndex = 0;
		m_renderData.quadIndexCount = 0;
		m_renderData.quadVertexPtrPosition = m_renderData.quadVertexBase;
	}

	void SpriteBatcher::NextBatch() {
		Flush();
		StartBatch();
	}

	void SpriteBatcher::Flush() {

		for (uint32_t i = 0; i < m_renderData.TextureSlotIndex; i++) {
			m_renderData.TextureSlots[i]->Bind(i);
		}

		uint32_t dataSize = (uint32_t)((uint8_t*)m_renderData.quadVertexPtrPosition - (uint8_t*)m_renderData.quadVertexBase);
		Renderer::SetBufferData(m_renderData.quadVertexBase, dataSize);
		Renderer::DrawIndexed(m_renderData.ViewProjection, m_renderData.quadIndexCount);
		m_renderData.RenderStats.DrawCalls++;
	}

}