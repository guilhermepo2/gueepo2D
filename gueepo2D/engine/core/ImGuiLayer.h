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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float DeltaTime) override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};
}