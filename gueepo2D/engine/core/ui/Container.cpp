#include "Container.h"

namespace gueepo {

	bool Container::ProcessInput(const InputState& CurrentInputState) {
		for (int i = 0; i < m_controls.size(); i++) {
			if (m_controls[i]->ProcessInput(CurrentInputState)) {
				return true;
			}
		}

		return false;
	}

	void Container::Update(float DeltaTime) {
		for (int i = 0; i < m_controls.size(); i++) {
			m_controls[i]->Update(DeltaTime);
		}
	}

	void Container::Render() {
		for (int i = 0; i < m_controls.size(); i++) {
			m_controls[i]->Render();
		}
	}

}