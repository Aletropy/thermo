#define THERMO_ENTRY_POINT
#include <Thermo.h>

#include "imgui.h"
#include "Graphics/Rendering/Framebuffer.h"

using namespace Thermo;

static int WIDTH = 960, HEIGHT = 540;

class TestingSystem : public System
{
public:
    void Initialize() override
    {
        Batch2D::Initialize();

        Renderer::SetViewport(0.0f, 0.0f, WIDTH, HEIGHT);
        m_Camera = CreateRef<Camera2D>(WIDTH, HEIGHT, 5.0f);

        m_DiamondPickaxeTexture = Texture2D::Create("assets/textures/diamond_pickaxe.png");
        m_DiamondAxeTexture = Texture2D::Create("assets/textures/diamond_axe.png");
        m_DiamondSwordTexture = Texture2D::Create("assets/textures/diamond_sword.png");
        m_DiamondShovelTexture = Texture2D::Create("assets/textures/diamond_shovel.png");
        m_DiamondTexture = Texture2D::Create("assets/textures/diamond.png");

        Batch2D::SetCamera(m_Camera);
    }

    void Update(float deltaTime) override
    {
        Renderer::SetClearColor(Colors::NICE_DARK_BLUE);
        Renderer::Clear();

        Batch2D::BeginBatch();

        Batch2D::PushQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_DiamondTexture);
        Batch2D::PushQuad({3.5f, 0.0f}, {1.0f, 1.0f}, m_DiamondAxeTexture);
        Batch2D::PushQuad({-3.5f, 0.0f}, {1.0f, 1.0f}, m_DiamondPickaxeTexture);
        Batch2D::PushQuad({0.0f, -3.5f}, {1.0f, 1.0f}, m_DiamondSwordTexture);
        Batch2D::PushQuad({0.0f, 3.5f}, {1.0f, 1.0f}, m_DiamondShovelTexture);


        Batch2D::EndBatch();
    }

private:
    Ref<Camera2D> m_Camera;
    Ref<Texture2D> m_DiamondTexture;
    Ref<Texture2D> m_DiamondSwordTexture;
    Ref<Texture2D> m_DiamondPickaxeTexture;
    Ref<Texture2D> m_DiamondAxeTexture;
    Ref<Texture2D> m_DiamondShovelTexture;
};

Application* Thermo::CreateDefaultApplication()
{
    ApplicationSpecification spec;
    spec.WindowWidth = WIDTH;
    spec.WindowHeight = HEIGHT;
    spec.WindowTitle = "Thermo Editor";

    auto* app = new Application(spec);
    app->PushSystem<TestingSystem>();

    return app;
}