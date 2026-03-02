cmake_minimum_required(VERSION 3.10.0)
project(Lite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(imgui CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(Lite SHARED)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui
                                              SDL3::SDL3
                                              $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
                                              SDL3_ttf::SDL3_ttf
                                              spdlog::spdlog_header_only)

target_sources(${PROJECT_NAME} PRIVATE "src/core/log.cpp"
                                       "src/core/context.cpp"
                                       "src/core/initialize.cpp"
                                       "src/window/window.cpp"
                                       "src/renderer/renderer.cpp"
                                       "src/event/event.cpp")

target_compile_definitions(${PROJECT_NAME} PRIVATE LITE_EXPORTS)