cmake_minimum_required(VERSION 3.10.0)
project(YiaLite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")

add_library(${PROJECT_NAME} SHARED)

set(C_SRC "src/c_api(discard)/yialite.cpp")

set(CXX_SRC "src/cpp_api/core/logger.cpp"
            "src/cpp_api/core/context.cpp"
            "src/cpp_api/core/initialize.cpp"
            "src/cpp_api/core/log.cpp"
            "src/cpp_api/audio/audio_manager.cpp"
            "src/cpp_api/input/input.cpp"
            "src/cpp_api/devui/devui.cpp")

set(THIRD_PARTY_SRC "src/cpp_api/devui/imgui/imgui.cpp"
                    "src/cpp_api/devui/imgui/imgui_demo.cpp"
                    "src/cpp_api/devui/imgui/imgui_draw.cpp"
                    "src/cpp_api/devui/imgui/imgui_tables.cpp"
                    "src/cpp_api/devui/imgui/imgui_widgets.cpp"
                    "src/cpp_api/devui/imgui/backends/imgui_impl_sdl3.cpp"
                    "src/cpp_api/devui/imgui/backends/imgui_impl_sdlrenderer3.cpp"
                    "src/cpp_api/audio/miniaudio/miniaudio.cpp"
                    "src/cpp_api/audio/miniaudio/libvorbis/miniaudio_libvorbis.c")

target_sources(${PROJECT_NAME} PRIVATE ${CXX_SRC} ${C_SRC} ${THIRD_PARTY_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${MINIAUDIO_INCLUDE_DIRS}
                                                   "src/cpp_api/devui/imgui"
                                                   "src/cpp_api/devui/imgui/backends")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3
                                              $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
                                              SDL3_ttf::SDL3_ttf
                                              spdlog::spdlog_header_only
                                              Vorbis::vorbisfile)

target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS)