#ifndef THERMOENGINE_SHADER_H
#define THERMOENGINE_SHADER_H

namespace Thermo
{

    class Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Bind() const;
        static void Unbind() ;

        static Ref<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);

    private:
        static std::string ReadFile(const std::string& path);
        static uint32_t CompileShader(uint32_t type, const std::string& source);

    private:
        uint32_t m_Id;
    };

} // Thermo

#endif //THERMOENGINE_SHADER_H
