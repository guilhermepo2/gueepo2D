// Controls are the basic building block of the UI
// They define the interface that any derived control may implement their own behavior
#pragma once
#include "core/Common.h"
#include "core/math/math.h"

namespace gueepo {

	struct InputState;

	class Control {
	public:
		virtual bool ProcessInput(const InputState& CurrentInputState) { unreferenced(CurrentInputState); return false; }
		virtual void Update(float DeltaTime) {}	// Controls should update themselves
		virtual void Render() {}					// Controls should render themselves

		gueepo::math::vec2 GetPosition() const { return position; }
		inline void SetPosition(gueepo::math::vec2 pos) { position = pos; }

	protected:
		gueepo::math::vec2 position;
		bool isVisible;

		// rectangle? to define boundaries
		// alpha?
		// foreground and background color?
		// bool enabled?
		// bool focused?
		// bool mouseOver?

		// events? on focus received, on focus lost, on mouse enter, on mouse leave
	};
}
