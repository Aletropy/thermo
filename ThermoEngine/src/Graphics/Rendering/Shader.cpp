#include "ThermoPch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Thermo
{
    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    {
        uint32_t vs = CompileShader(GL_VERTEX_SHADER, ReadFile(vertexPath));
        uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, ReadFile(fragmentPath));

        m_Id = glCreateProgram();

        glAttachShader(m_Id, vs);
        glAttachShader(m_Id, fs);

        glLinkProgram(m_Id);

        int success = 0;
        glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_Id, 512, nullptr, infoLog);
            THERMO_ASSERT(false, "%s", infoLog);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_Id);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_Id);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    std::string Shader::ReadFile(const std::string &path)
    {
        std::ifstream fileStream(path);

        if (!fileStream.is_open())
        {
            THERMO_ASSERT(false, "Could not open file: %s", path.c_str());
            return "";
        }

        std::stringstream content;
        std::string line;

        while(std::getline(fileStream, line))
        {
            content << line << "\n";
        }

        return content.str();
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string &source)
    {
        const char* c_str = source.c_str();

        uint32_t shader = glCreateShader(type);

        glShaderSource(shader, 1, &c_str, nullptr);
        glCompileShader(shader);

        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            THERMO_ASSERT(false, "%s", infoLog);
        }

        return shader;
    }

    Ref<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return CreateRef<Shader>(vertexPath, fragmentPath);
    }

    void Shader::UploadMatrix4x4(const std::string &name, float *values) const
    {
        int location = glGetUniformLocation(m_Id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, values);
    }

    void Shader::UploadIntArray(const std::string &name, int *values, int count)
    {
        int location = glGetUniformLocation(m_Id, name.c_str());
        glUniform1iv(location, count, values);
    }
} // Thermo