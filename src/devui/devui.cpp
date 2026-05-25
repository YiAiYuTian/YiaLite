#include "devui.h"
#include "../renderer/renderer2d.h"
#include "../window/window.h"
#include "../utils/memory/allocator.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>

namespace yialite
{

void* yialiteImGuiMalloc(size_t sz, void* user_data)
{
    return ALLOCATE_SIZED(sz);
}

void yialiteImGuiFree(void* ptr, void* user_data)
{
    DEALLOCATE(ptr);
}

struct DevUI::Impl
{
    SDL_Renderer* sdl_renderer = nullptr;
};

DevUI::DevUI(Window* window, Renderer2D* renderer)
{
    m_impl = ALLOCATE(DevUI::Impl);
    m_impl->sdl_renderer = reinterpret_cast<SDL_Renderer*>(renderer->getNativeHandle());

    ImGui::SetAllocatorFunctions(yialiteImGuiMalloc, yialiteImGuiFree);

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

    DEALLOCATE(m_impl);
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