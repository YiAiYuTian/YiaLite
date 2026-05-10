cmake_minimum_required(VERSION 3.10.0)
project(YiaLite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED)

#set(C_SRC "src/c_api(discard)/yialite.cpp")

set(YIA_HEADERS "src/cpp_api/audio/audio_manager.h"
                "src/cpp_api/core/config.h"
                "src/cpp_api/core/context.h"
                "src/cpp_api/core/core.h"
                "src/cpp_api/core/initialize.h"
                "src/cpp_api/core/log.h"
                "src/cpp_api/core/yialite_exception.h"
                "src/cpp_api/devui/devui.h"
                "src/cpp_api/event/event.h"
                "src/cpp_api/event/keycode.h"
                "src/cpp_api/event/mouse_button.h"
                "src/cpp_api/input/input.h"
                "src/cpp_api/input/scancode.h"
                "src/cpp_api/math/math.h"
                "src/cpp_api/renderer/renderer2d.h"
                "src/cpp_api/renderer/render_color.h"
                "src/cpp_api/renderer/texture/texture2d.h"
                "src/cpp_api/utils/containers/yia_hashmap.h"
                "src/cpp_api/utils/containers/yia_list.h"
                "src/cpp_api/utils/containers/yia_pair.h"
                "src/cpp_api/utils/memory/allocator.h"
                "src/cpp_api/utils/string/yia_string.h"
                "src/cpp_api/utils/string/yia_string_view.h"
                "src/cpp_api/utils/utility.h"
                "src/cpp_api/utils/singleton.h"
                "src/cpp_api/utils/hash_key.h"
                "src/cpp_api/utils/base_types.h"
                "src/cpp_api/window/window.h")

set(YIA_SOURCES "src/cpp_api/core/logger.cpp"
                "src/cpp_api/core/context.cpp"
                "src/cpp_api/core/initialize.cpp"
                "src/cpp_api/core/log.cpp"
                "src/cpp_api/audio/audio_manager.cpp"
                "src/cpp_api/input/input.cpp"
                "src/cpp_api/window/window.cpp"
                "src/cpp_api/renderer/renderer2d.cpp"
                "src/cpp_api/renderer/texture/texture2d.cpp"
                "src/cpp_api/event/event.cpp"
                "src/cpp_api/devui/devui.cpp"
                "src/cpp_api/utils/memory/allocator.cpp"
                "src/cpp_api/utils/string/yia_string.cpp"
                "src/cpp_api/utils/string/yia_string_view.cpp")

set(THIRD_PARTY_SOURCES "src/cpp_api/thirdparty/imgui/imgui.cpp"
                        "src/cpp_api/thirdparty/imgui/imgui_demo.cpp"
                        "src/cpp_api/thirdparty/imgui/imgui_draw.cpp"
                        "src/cpp_api/thirdparty/imgui/imgui_tables.cpp"
                        "src/cpp_api/thirdparty/imgui/imgui_widgets.cpp"
                        "src/cpp_api/thirdparty/imgui/backends/imgui_impl_sdl3.cpp"
                        "src/cpp_api/thirdparty/imgui/backends/imgui_impl_sdlrenderer3.cpp"
                        "src/cpp_api/thirdparty/miniaudio/miniaudio.cpp"
                        "src/cpp_api/thirdparty/miniaudio/libvorbis/miniaudio_libvorbis.c"
                        "src/cpp_api/thirdparty/stb_image/stb_image.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${YIA_SOURCES} ${THIRD_PARTY_SOURCES} ${YIA_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE "src/cpp_api/thirdparty/imgui"
                                                   "src/cpp_api/thirdparty/imgui/backends")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3
                                              spdlog::spdlog_header_only
                                              Vorbis::vorbisfile)

target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS YIALITE_SHARED)