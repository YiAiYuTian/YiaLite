# ===========================================================================
# Third-party libraries — all built as STATIC, absorbed into YiaLite.dll
#
# CRITICAL: Every third-party must be STATIC. If any becomes SHARED (DLL),
# its code lives outside YiaLite.dll → consumer would need that DLL too.
# This breaks our "only YiaLite.dll needed" contract.
#
# Strategy:
#   1. Set BUILD_SHARED_LIBS=OFF as a NORMAL variable (not CACHE FORCE)
#      — normal vars override cache in the same scope, more reliable
#   2. Pass per-project options via -D flags to add_subdirectory
#   3. Disable all install/test/example overhead
# ===========================================================================

# Global: force all add_library() calls to STATIC by default
set(BUILD_SHARED_LIBS OFF)

# ===========================================================================
# SDL3
# ===========================================================================
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_CPACK OFF CACHE BOOL "" FORCE)
add_subdirectory(SDL)

# ===========================================================================
# ogg
# ===========================================================================
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(INSTALL_PKG_CONFIG_MODULE OFF CACHE BOOL "" FORCE)
set(INSTALL_CMAKE_PACKAGE_MODULE OFF CACHE BOOL "" FORCE)
set(INSTALL_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(ogg)

# ===========================================================================
# vorbis
# ===========================================================================
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(VORBIS_INSTALL OFF CACHE BOOL "" FORCE)
set(INSTALL_CMAKE_PACKAGE_MODULE OFF CACHE BOOL "" FORCE)
set(INSTALL_PKG_CONFIG_MODULE OFF CACHE BOOL "" FORCE)
add_subdirectory(vorbis)

# ===========================================================================
# spdlog
# ===========================================================================
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_ALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE_HO OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS_HO OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_WARNINGS OFF CACHE BOOL "" FORCE)
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL_HO OFF CACHE BOOL "" FORCE)
add_subdirectory(spdlog)