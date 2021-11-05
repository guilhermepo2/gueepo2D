#pragma once
#include "core/layer/Layer.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"

namespace gueepo {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(float DeltaTime);
		void OnEvent(Event& e);

	private:

		bool OnMouseWheel(MouseScrolledEvent& e);
		bool OnMouseButtonDown(MouseButtonPressedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		// bool OnWindowMoved(KeyReleasedEvent& e);
		// bool OnWindowFocusGained(KeyReleasedEvent& e);
		// bool OnWindowFocusLost(KeyReleasedEvent& e);
	};
}