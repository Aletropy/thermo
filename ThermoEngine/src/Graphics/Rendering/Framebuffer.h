#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace Thermo {

class Framebuffer 
{
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Bind() const;
    void Invalidate(int width, int height);

    uint32_t GetId() const { return m_Id; }

    static void Unbind();

    static Ref<Framebuffer> Create(int width, int height);
private:
    uint32_t m_Id;
    uint32_t m_ColorAttachment, m_DepthAttachment;
    int m_Width, m_Height;
};

} // Thermo

#endif //FRAMEBUFFER_H
