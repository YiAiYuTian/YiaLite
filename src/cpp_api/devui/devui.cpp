#include "devui.h"
#include "../renderer/renderer2d.h"
#include "../window/window.h"

#include "../thirdparty/imgui/imgui.h"
#include "../thirdparty/imgui/backends/imgui_impl_sdl3.h"
#include "../thirdparty/imgui/backends/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>

namespace yialite
{

struct DevUI::Impl
{
    SDL_Renderer* sdl_renderer = nullptr;
};

DevUI::DevUI(Window* window, Renderer2D* renderer)
{
    m_impl = new DevUI::Impl();
    m_impl->sdl_renderer = reinterpret_cast<SDL_Renderer*>(renderer->getNativeHandle());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(reinterpret_cast<SDL_Window*>(window->getNativeHandle()), m_impl->sdl_renderer);
    ImGui_ImplSDLRenderer3_Init(m_impl->sdl_renderer);
}

DevUI::~DevUI()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    delete m_impl;
}

void DevUI::onUpdate()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void DevUI::onRender()
{
    auto& renderer = m_impl->sdl_renderer;
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

}