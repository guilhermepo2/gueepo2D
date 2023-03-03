#pragma once
#include "core/containers/vector.h"
#include "core/ui/Control.h"
#include "core/ui/Container.h"

namespace gueepo {
	class UIManager {
	public:
		UIManager(int width, int height);
		~UIManager();

		void Push(Control* uiElement);
		void Pop();

	private:
		int m_width;
		int m_height;
		gueepo::vector<Control*> m_UIElements;
	};
}