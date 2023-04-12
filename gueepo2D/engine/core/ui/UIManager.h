#pragma once
#include "core/containers/vector.h"
#include "core/ui/Control.h"
#include "core/ui/Container.h"

namespace gueepo {
	struct InputState;

	class UIManager {
	public:
		UIManager(int width, int height);
		~UIManager();

		bool ProcessInput(const InputState& CurrentInputState);
		void Update(float DeltaTime);
		void Render();

		void Push(Control* uiElement);
		void Pop();

	private:
		int m_width;
		int m_height;
		gueepo::vector<Control*> m_UIElements;
	};
}