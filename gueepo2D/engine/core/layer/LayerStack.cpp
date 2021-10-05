#include "gueepo2Dpch.h"
#include "LayerStack.h"

namespace gueepo {

	LayerStack::~LayerStack() {
		for (Layer* l : m_Layers) {
			l->OnDetach();
			delete l;
		}
	}

	void LayerStack::PushLayer(Layer* _layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, _layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* _layer) {
		m_Layers.emplace_back(_layer);
	}

	void LayerStack::PopLayer(Layer* _layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, _layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			_layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* _layer) {
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), _layer);
		if (it != m_Layers.end()) {
			_layer->OnDetach();
			m_Layers.erase(it);
		}
	}

}