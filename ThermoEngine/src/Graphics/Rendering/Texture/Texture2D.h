#ifndef TEXTURE2D_H
#define TEXTURE2D_H

namespace Thermo
{
    class Texture2D
    {
    public:
        explicit Texture2D(const std::string &filepath, bool flip = true);

        Texture2D(int width, int height);

        ~Texture2D();

        void Bind(uint32_t slot = 0) const;

        [[nodiscard]] uint32_t GetId() const { return m_Id; }
        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }
        const std::string &GetFilepath() const { return m_Filepath; }

        static Ref<Texture2D> Create(const std::string &filepath, bool flip = true);

    private:
        uint32_t m_Id{};
        int m_Width, m_Height;
        std::string m_Filepath;
    };
} // Thermo

#endif //TEXTURE2D_H
