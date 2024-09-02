#ifndef TEXTURE2D_H
#define TEXTURE2D_H

namespace Thermo
{
    class Texture2D
    {
    public:
        explicit Texture2D(const std::string& filepath);
        ~Texture2D();

        void Bind(uint32_t slot = 0) const;

        [[nodiscard]] inline uint32_t GetId() const { return m_Id; }

        static Ref<Texture2D> Create(const std::string& filepath);
    private:
        uint32_t m_Id{};
    };

} // Thermo

#endif //TEXTURE2D_H
