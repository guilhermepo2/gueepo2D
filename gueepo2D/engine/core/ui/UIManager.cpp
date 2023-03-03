#include "UIManager.h"

namespace gueepo {

	UIManager::UIManager(int width, int height) : m_width(width), m_height(height) {}

	UIManager::~UIManager() {
		m_UIElements.clear(); // AFAIK this should call the destructor on every element
	}

	void UIManager::Push(Control* uiElement) {
		m_UIElements.insert(0, uiElement);
	}

	void UIManager::Pop() {
		m_UIElements.erase(0);
	}

}