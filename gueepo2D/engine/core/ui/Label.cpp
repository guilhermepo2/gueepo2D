#include "Label.h"

#include "core/renderer/Color.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/FontSprite.h"

namespace gueepo {
	
	Label::Label(const gueepo::string& text, gueepo::FontSprite* fontSprite) : m_internalText(text), m_fontRef(fontSprite), m_alignment(LEFT) {}

	bool Label::ProcessInput(const InputState& CurrentInputState) {
		unreferenced(CurrentInputState);
		return false;
	}

	void Label::Update(float DeltaTime) {
		unreferenced(DeltaTime);
	}

	void Label::Render() {
		gueepo::math::vec2 positionOffset;
		positionOffset.x = 0.0f;
		positionOffset.y = 0.0f;

		switch (m_alignment) {
		case LEFT:
			break;
		case CENTER:
			positionOffset.x -= (m_fontRef->GetWidthOf(m_internalText) / 2.0f);
			break;
		case RIGHT:
			// not sure? have to check the boundaries of this elements or of the parent to where it ends
			// and then the position is whereItEnds - width
			break;
		}

		gueepo::Renderer::DrawString(
			m_fontRef,
			m_internalText,
			position + positionOffset,
			1.0f,
			gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}

}