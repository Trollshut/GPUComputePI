#include "Shader.h"

#include <glad/gles2.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader()
    : m_ProgramID(0)
{
}

Shader::~Shader()
{
    if (m_ProgramID)
        glDeleteProgram(m_ProgramID);
}

bool Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);

    uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vertexShader || !fragmentShader)
        return false;

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    GLint success = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, infoLog.data());

        std::cerr << "Shader linking failed:\n" << infoLog.data() << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(m_ProgramID);
        m_ProgramID = 0;

        return false;
    }

    glDetachShader(m_ProgramID, vertexShader);
    glDetachShader(m_ProgramID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Shader::Bind() const
{
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

std::string Shader::ReadFile(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
    uint32_t shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

        std::cerr << "Shader compilation failed:\n" << infoLog.data() << std::endl;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
