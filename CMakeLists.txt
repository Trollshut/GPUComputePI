cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(App)
set(CMAKE_CXX_STANDARD 20)

# Force Raspberry Pi config
set(PLATFORM_RPI TRUE)

# Dependencies
## GLFW for Raspberry Pi (with native platform support)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE) # or OFF if you're testing Wayland
set(GLFW_USE_MIR OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw3
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
)
FetchContent_GetProperties(glfw3)
if (NOT glfw3_POPULATED)
    FetchContent_Populate(glfw3)
    add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
endif()

## OpenGL ES 3.0 (find_package not used, GLAD handles it)
# glad loader for GLES2 API (which includes 3.0 support)
FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)

FetchContent_GetProperties(glad)
if (NOT glad_POPULATED)
    FetchContent_Populate(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL
        LOADER API gles2=3.0
    )
endif()
set_target_properties(glad PROPERTIES FOLDER "Dependencies")

## GLM
FetchContent_Declare(
    glm
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()
set_target_properties(glm PROPERTIES FOLDER "Dependencies")

# Projects
add_subdirectory(App)
