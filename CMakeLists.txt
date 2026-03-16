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

set(C_SRC "src/c_api/yialite.cpp")

set(CXX_SRC "src/cpp_api/core/logger.cpp"
            "src/cpp_api/core/context.cpp"
            "src/cpp_api/core/initialize.cpp"
            "src/cpp_api/core/log.cpp"
            "src/cpp_api/audio/audio_manager.cpp"
            "src/cpp_api/audio/miniaudio/miniaudio.cpp"
            "src/cpp_api/audio/miniaudio/libvorbis/miniaudio_libvorbis.c"
            "src/cpp_api/input/input.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${CXX_SRC} ${C_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${MINIAUDIO_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui
                                              SDL3::SDL3
                                              $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
                                              SDL3_ttf::SDL3_ttf
                                              spdlog::spdlog_header_only
                                              Vorbis::vorbisfile)

target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS)