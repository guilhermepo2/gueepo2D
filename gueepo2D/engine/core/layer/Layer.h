#pragma once
#include "core/events/Event.h"

namespace gueepo {
	class Layer {
	public:
		Layer(const std::string& _name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float DeltaTime) { unreferenced(DeltaTime); }
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) { unreferenced(e); }

	private:
		// #todo YEET STL
		std::string m_LayerName;
	};
}