#pragma once
#include "core/events/Event.h"
#include "core/input/Input.h"

namespace gueepo {
	class Layer {
	public:
		Layer(const std::string& _name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float DeltaTime) { unreferenced(DeltaTime); }
		virtual void OnInput(const InputState& currentInputState) { unreferenced(currentInputState); }
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) { unreferenced(e); }

	private:
		// #todo YEET STL
		std::string m_LayerName;
	};
}