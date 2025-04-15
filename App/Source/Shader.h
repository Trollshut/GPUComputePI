#pragma once

#include <string>
#include <filesystem>

class Shader
{
public:
    Shader();
    ~Shader();

    bool Load(const std::string& vertexPath, const std::string& fragmentPath);
    void Bind() const;
    void Unbind() const;

    uint32_t GetProgramID() const { return m_ProgramID; }

private:
    uint32_t m_ProgramID;

    std::string ReadFile(const std::filesystem::path& path);
    uint32_t CompileShader(uint32_t type, const std::string& source);
};
