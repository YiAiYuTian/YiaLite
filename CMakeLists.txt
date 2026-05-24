cmake_minimum_required(VERSION 3.10.0)
project(YiaLite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)

if(MSVC_STATIC_MT_LIB OR MSVC_STATIC_MD_LIB OR MINGW_STATIC_MD_LIB OR CLANG_STATIC_MD_LIB)
    add_library(${PROJECT_NAME} STATIC)
elseif(MSVC_STATIC_MD_DLL OR MINGW_STATIC_MD_DLL OR CLANG_STATIC_MD_DLL)
    add_library(${PROJECT_NAME} SHARED)
elseif(
    (NOT MSVC_STATIC_MD_DLL AND NOT MSVC_STATIC_MD_LIB AND NOT MSVC_STATIC_MT_LIB) OR 
    (NOT MINGW_STATIC_MD_LIB AND NOT MINGW_STATIC_MD_DLL) OR 
    (NOT CLANG_STATIC_MD_LIB AND NOT CLANG_STATIC_MD_DLL))
    add_library(${PROJECT_NAME} SHARED)
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()

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
                "src/cpp_api/utils/memory/memory_pool.h"
                "src/cpp_api/utils/memory/memory.h"
                "src/cpp_api/utils/string/yia_string.h"
                "src/cpp_api/utils/string/yia_string_view.h"
                "src/cpp_api/utils/utility.h"
                "src/cpp_api/utils/singleton.h"
                "src/cpp_api/utils/hash_key.h"
                "src/cpp_api/utils/delegate.h"
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
                "src/cpp_api/utils/memory/memory_pool.cpp"
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

if(MSVC_STATIC_MD_DLL OR MINGW_STATIC_MD_DLL OR CLANG_STATIC_MD_DLL)
    target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS YIALITE_SHARED)
elseif(
    (NOT MSVC_STATIC_MD_DLL AND NOT MSVC_STATIC_MD_LIB AND NOT MSVC_STATIC_MT_LIB) OR 
    (NOT MINGW_STATIC_MD_LIB AND NOT MINGW_STATIC_MD_DLL) OR
    (NOT CLANG_STATIC_MD_LIB AND NOT CLANG_STATIC_MD_DLL))
    target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS YIALITE_SHARED)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY src/cpp_api/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/yialite
  FILES_MATCHING PATTERN "*.h"

  PATTERN "logger.h" EXCLUDE
)

install(
  FILES LICENSE
  DESTINATION ${CMAKE_INSTALL_DATADIR}/yialite
)
install(
  DIRECTORY licenses/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/yialite/licenses
  FILES_MATCHING
    PATTERN "LICENSE"
    PATTERN "LICENSE.txt"
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT YiaLiteTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/yialite
)

install(
  EXPORT YiaLiteTargets
  NAMESPACE YiaLite::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YiaLite
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/YiaLiteConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/YiaLiteConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YiaLite
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/YiaLiteConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/YiaLiteConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/YiaLiteConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YiaLite
)