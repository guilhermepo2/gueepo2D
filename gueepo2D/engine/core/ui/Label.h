#pragma once
#include "Control.h"

namespace gueepo {
	class Label : public Control {
	public:
		bool ProcessInput(const InputState& CurrentInputState) override;
		void Update(float DeltaTime) override;
		void Render() override;

	protected:
		// string of text? all the textures?
	};
}