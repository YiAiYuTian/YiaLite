cmake_minimum_required(VERSION 3.10.0)
project(YiaLite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(imgui CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE "src/core/log.cpp"
                                       "src/core/context.cpp"
                                       "src/core/initialize.cpp"
                                       "src/window/window.cpp"
                                       "src/renderer/renderer.cpp"
                                       "src/event/event.cpp"
                                       "src/audio/audio_system.cpp"
                                       "src/audio/miniaudio/miniaudio.cpp"
                                       "src/audio/miniaudio/libvorbis/miniaudio_libvorbis.c"
                                       "src/input/input.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${MINIAUDIO_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui
                                              SDL3::SDL3
                                              $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
                                              SDL3_ttf::SDL3_ttf
                                              spdlog::spdlog_header_only
                                              Vorbis::vorbisfile)

target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS)