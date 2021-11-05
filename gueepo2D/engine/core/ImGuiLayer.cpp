#include "gueepo2Dpch.h"
#include "ImGuiLayer.h"
#include "Application.h"
#include "core/events/EventDispatcher.h"

// #todo: maybe I can change this to #include "thirdparty/imgui-docking/backends/(...)" ?
// #also: this is temporary stuff
#include "platform/SDL2/imgui_impl_sdl.h"
#include "platform/OpenGL/imgui_impl_opengl3.h"
#include <SDL.h>
#include <glad/glad.h>
static const char* opengl_version = "#version 450";
bool show_demo_window = true;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// #todo this is being redefined here! maybe put it on a common.h?
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)



namespace gueepo {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		// #todo: have to get access to the application
		// #todo have to get access to gl context somehow?
		// #todo: ehrm... this is kinda weird but kinda works if we always have one window and one context?
		ImGui_ImplSDL2_InitForOpenGL(SDL_GL_GetCurrentWindow(), SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL3_Init(opengl_version);
	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate(float DeltaTime) {
		unreferenced(DeltaTime);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window) {
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		ImGui::Render();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::Get();
		io.DeltaTime = DeltaTime;
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
	}

	void ImGuiLayer::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(ImGuiLayer::OnMouseWheel));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(ImGuiLayer::OnMouseButtonDown));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT(ImGuiLayer::OnKeyReleased));
	}

	bool ImGuiLayer::OnMouseWheel(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		if (e.GetXOffset() > 0) io.MouseWheelH += 1;
		if (e.GetXOffset() < 0) io.MouseWheelH -= 1;
		if (e.GetYOffset() > 0) io.MouseWheel += 1;
		if (e.GetYOffset() < 0) io.MouseWheel -= 1;
		return true;
	}

	bool ImGuiLayer::OnMouseButtonDown(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == SDL_BUTTON_LEFT) { ImGui_ImplSDL2_SetMouseButtonPressed(0, true); }
		if (e.GetMouseButton() == SDL_BUTTON_RIGHT) { ImGui_ImplSDL2_SetMouseButtonPressed(1, true); }
		if (e.GetMouseButton() == SDL_BUTTON_MIDDLE) { ImGui_ImplSDL2_SetMouseButtonPressed(2, true); }
		return true;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.GetKeyCode();
		io.KeysDown[key] = true;

		io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
		io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
		io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
#ifdef _WIN32
		io.KeySuper = false;
#else
		io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif
		return true;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.GetKeyCode();
		io.KeysDown[key] = false;

		io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
		io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
		io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
#ifdef _WIN32
		io.KeySuper = false;
#else
		io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif
		return true;
	}

	bool ImGuiLayer::OnWindowClosed(WindowCloseEvent& e) {
		unreferenced(e);

		ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(SDL_GL_GetCurrentWindow());
		viewport->PlatformRequestClose = true;
		return true;
	}

	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& e) {
		unreferenced(e);

		ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(SDL_GL_GetCurrentWindow());
		viewport->PlatformRequestResize = true;
		return true;
	}

}


/*
bool ImGui_ImplSDL2_ProcessEvent(const SDL_Event* event)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL2_Data* bd = ImGui_ImplSDL2_GetBackendData();

	switch (event->type)
	{
	// Multi-viewport support
	case SDL_WINDOWEVENT:
		Uint8 window_event = event->window.event;
		if (window_event == SDL_WINDOWEVENT_CLOSE || window_event == SDL_WINDOWEVENT_MOVED || window_event == SDL_WINDOWEVENT_RESIZED || window_event == SDL_WINDOWEVENT_FOCUS_GAINED || window_event == SDL_WINDOWEVENT_FOCUS_LOST)
			if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle((void*)SDL_GetWindowFromID(event->window.windowID)))
			{
				if (window_event == SDL_WINDOWEVENT_MOVED)
					viewport->PlatformRequestMove = true;
				if (window_event == SDL_WINDOWEVENT_FOCUS_GAINED)
					io.AddFocusEvent(true);
				else if (window_event == SDL_WINDOWEVENT_FOCUS_LOST)
					io.AddFocusEvent(false);
				return true;
			}
		break;
	}
	return false;
}
*/
