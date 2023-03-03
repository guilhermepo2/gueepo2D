#include "UIManager.h"

namespace gueepo {

	UIManager::UIManager(int width, int height) : m_width(width), m_height(height) {}

	UIManager::~UIManager() {
		m_UIElements.clear(); // AFAIK this should call the destructor on every element
	}

	bool UIManager::ProcessInput(const InputState& CurrentInputState) {
		for (int i = 0; i < m_UIElements.size(); i++) {
			if (m_UIElements[i]->ProcessInput(CurrentInputState)) {
				return true;
			}
		}

		return false;
	}

	void UIManager::Update(float DeltaTime) {
		for (int i = 0; i < m_UIElements.size(); i++) {
			m_UIElements[i]->Update(DeltaTime);
		}
	}

	void UIManager::Render() {
		for (int i = 0; i < m_UIElements.size(); i++) {
			m_UIElements[i]->Render();
		}
	}

	void UIManager::Push(Control* uiElement) {
		m_UIElements.insert(0, uiElement);
	}

	void UIManager::Pop() {
		m_UIElements.erase(0);
	}

}