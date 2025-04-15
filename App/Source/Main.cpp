#include <iostream>
#include <filesystem>
#include <glm/glm.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gles2.h> 

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Shader.h"
#include "Renderer.h"

static const std::filesystem::path s_ShaderDir = "../../App/Shaders";
static const std::filesystem::path s_VertexShaderPath   = s_ShaderDir / "Rectangle.vert";
static const std::filesystem::path s_FragmentShaderPath = s_ShaderDir / "Rectangle.frag";

static void ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	int width = 1280;
	int height = 720;

	GLFWwindow* window = glfwCreateWindow(width, height, "Red Rectangle", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, KeyCallback);
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLES2((GLADloadfunc)glfwGetProcAddress)) {
	std::cerr << "Failed to initialize GLAD" << std::endl;
	return -1;
	}

	glfwSwapInterval(1);

	// Setup Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 300 es"); // GLES 3.0 shader version


	// ✅ Correct GLAD 2 function call
	if (!gladLoadGLES2((GLADloadfunc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSwapInterval(1);

	Shader shader;
	if (!shader.Load(s_VertexShaderPath.string(), s_FragmentShaderPath.string()))
	{
		std::cerr << "Failed to load shaders\n";
		return -1;
	}

	Renderer renderer;
	renderer.Initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render red quad
		shader.Bind();
		renderer.RenderQuad();

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}


	renderer.Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
