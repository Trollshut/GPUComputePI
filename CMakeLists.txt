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
        LOADER API gles2=3.0 egl=1.5
    )
endif()
set_target_properties(glad PROPERTIES FOLDER "Dependencies")

# ImGui (docking branch)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)

    set(IMGUI_SRC_DIR ${imgui_SOURCE_DIR})

    add_library(imgui
        ${IMGUI_SRC_DIR}/imgui.cpp
        ${IMGUI_SRC_DIR}/imgui_draw.cpp
        ${IMGUI_SRC_DIR}/imgui_tables.cpp
        ${IMGUI_SRC_DIR}/imgui_widgets.cpp
        ${IMGUI_SRC_DIR}/imgui_demo.cpp
    )

    add_library(imgui_impl
        ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_SRC_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_include_directories(imgui PUBLIC ${IMGUI_SRC_DIR})
    target_include_directories(imgui_impl PUBLIC
        ${IMGUI_SRC_DIR}
        ${IMGUI_SRC_DIR}/backends
    )

    target_link_libraries(imgui_impl PUBLIC imgui glfw glad)

    set_target_properties(imgui PROPERTIES FOLDER "Dependencies")
    set_target_properties(imgui_impl PROPERTIES FOLDER "Dependencies")
endif()

# Projects
add_subdirectory(App)
