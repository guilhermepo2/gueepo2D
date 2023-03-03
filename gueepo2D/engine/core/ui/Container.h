#pragma once
#include "Control.h"

#include "core/containers/vector.h"

namespace gueepo {
	class Container : public Control {
	public:
		bool ProcessInput(const InputState& CurrentInputState) override;
		void Update(float DeltaTime) override;
		void Render() override;

	protected:
		gueepo::vector<Control*> m_controls;
	};
}