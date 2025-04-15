#include <iostream>
#include <filesystem>
#include <glm/glm.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gles2.h> // ✅ GLAD 2 GLES include
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
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		renderer.RenderQuad();

		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwGetFramebufferSize(window, &width, &height);
	}

	renderer.Shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
