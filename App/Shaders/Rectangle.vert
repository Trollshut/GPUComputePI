#version 300 es
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

void main()
{
    gl_Position = vec4(a_Position, 0.0, 1.0);
}
