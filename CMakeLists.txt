cmake_minimum_required(VERSION 3.10.0)
project(YiaLite VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED VCPKG_LIBRARY_LINKAGE)
  set(LIBRARY_LINKAGE ${VCPKG_LIBRARY_LINKAGE})
endif()

if(DEFINED VCPKG_CRT_LINKAGE)
  set(CRT_LINKAGE ${VCPKG_CRT_LINKAGE})
endif()

find_package(SDL3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")

if(LIBRARY_LINKAGE STREQUAL "static")
  add_library(${PROJECT_NAME} STATIC)
else()
  add_library(${PROJECT_NAME} SHARED)
  target_compile_definitions(${PROJECT_NAME} PRIVATE YIALITE_EXPORTS YIALITE_SHARED)
endif()

add_library(YiaLite::YiaLite ALIAS ${PROJECT_NAME})

if(MSVC)
  if(CRT_LINKAGE STREQUAL "static")
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  endif()
endif()

set(YIA_HEADERS "src/audio/audio_manager.h"
                "src/core/config.h"
                "src/core/context.h"
                "src/core/core.h"
                "src/core/initialize.h"
                "src/core/log.h"
                "src/core/yialite_exception.h"
                "src/devui/devui.h"
                "src/event/event.h"
                "src/event/keycode.h"
                "src/event/mouse_button.h"
                "src/input/input.h"
                "src/input/scancode.h"
                "src/math/math.h"
                "src/renderer/renderer2d.h"
                "src/renderer/render_color.h"
                "src/renderer/texture/texture2d.h"
                "src/utils/containers/yia_hashmap.h"
                "src/utils/containers/yia_list.h"
                "src/utils/containers/yia_pair.h"
                "src/utils/memory/allocator.h"
                "src/utils/memory/memory_pool.h"
                "src/utils/memory/memory.h"
                "src/utils/string/yia_string.h"
                "src/utils/string/yia_string_view.h"
                "src/utils/utility.h"
                "src/utils/singleton.h"
                "src/utils/hash_key.h"
                "src/utils/delegate.h"
                "src/utils/base_types.h"
                "src/window/window.h"
)

set(YIA_SOURCES "src/core/logger.cpp"
                "src/core/context.cpp"
                "src/core/initialize.cpp"
                "src/core/log.cpp"
                "src/audio/audio_manager.cpp"
                "src/input/input.cpp"
                "src/window/window.cpp"
                "src/renderer/renderer2d.cpp"
                "src/renderer/texture/texture2d.cpp"
                "src/event/event.cpp"
                "src/devui/devui.cpp"
                "src/utils/memory/allocator.cpp"
                "src/utils/memory/memory_pool.cpp"
                "src/utils/string/yia_string.cpp"
                "src/utils/string/yia_string_view.cpp"
                "src/thirdparty/miniaudio/miniaudio.cpp"
                "src/thirdparty/miniaudio/libvorbis/miniaudio_libvorbis.c"
                "src/thirdparty/stb_image/stb_image.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE ${YIA_SOURCES} ${YIA_HEADERS})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
  PRIVATE 
    ${Stb_INCLUDE_DIR}
    ${MINIAUDIO_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE 
    SDL3::SDL3
    spdlog::spdlog_header_only
    Vorbis::vorbisfile
  PUBLIC
    imgui::imgui
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/yialite
  FILES_MATCHING PATTERN "*.h"

  PATTERN "thirdparty" EXCLUDE
  PATTERN "logger.h" EXCLUDE
  PATTERN "miniaudio_libvorbis.h" EXCLUDE
)

if(NOT DEFINED PORT)
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
endif()

install(
  TARGETS ${PROJECT_NAME}
  EXPORT YiaLiteTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
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