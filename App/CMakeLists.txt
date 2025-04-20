# App

set(SOURCE_DIR "Source")

set(SOURCES
    ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/Shader.h
    ${SOURCE_DIR}/Shader.cpp
    ${SOURCE_DIR}/Renderer.h
    ${SOURCE_DIR}/Renderer.cpp
	${SOURCE_DIR}/ImGuiRenderer/ImGuiUI.h
)

# Create the executable
add_executable(App ${SOURCES})

# Link dependencies
target_link_libraries(App PRIVATE glfw glad)

# Link EGL and GLESv2 (for Raspberry Pi OpenGL ES 3.0 runtime)
target_link_libraries(App PRIVATE glfw glad imgui imgui_impl)

