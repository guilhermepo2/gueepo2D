#pragma once
#include "Control.h"

#include "core/containers/string.h"

namespace gueepo {
	
	class FontSprite;

	enum ALIGNMENT {
		LEFT,
		CENTER,
		RIGHT
	};

	class Label : public Control {
	public:
		Label(const gueepo::string& text, gueepo::FontSprite* fontSprite);

		bool ProcessInput(const InputState& CurrentInputState) override;
		void Update(float DeltaTime) override;
		void Render() override;

		inline void SetAlignment(ALIGNMENT alignment) { m_alignment = alignment; }

	protected:
		gueepo::string m_internalText;
		gueepo::FontSprite* m_fontRef;
		ALIGNMENT m_alignment;
	};
}