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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// #todo: have to get access to the application
		// #todo have to get access to gl context somehow?
		// #todo: ehrm... this is kinda weird but kinda works if we always have one window and one context?
		ImGui_ImplSDL2_InitForOpenGL(SDL_GL_GetCurrentWindow(), SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL3_Init(opengl_version);
	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(float DeltaTime) {
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = DeltaTime;
		
	}

	void ImGuiLayer::OnImGuiRender() {}

	void ImGuiLayer::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}
}
