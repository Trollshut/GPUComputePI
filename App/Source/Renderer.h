#pragma once

#include <cstdint>

struct Texture
{
	uint32_t Handle = 0;
	int Width = 0;
	int Height = 0;
};

struct Framebuffer
{
	uint32_t Handle = 0;
	Texture ColorAttachment;
};

class Renderer
{
public:
	void Initialize();
	void RenderQuad();
	void Shutdown();

private:
	uint32_t m_VAO = 0;
	uint32_t m_VBO = 0;
};
