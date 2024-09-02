#define THERMO_ENTRY_POINT
#include <Thermo.h>

#include "imgui.h"

using namespace Thermo;

class TestingSystem : public System
{
public:
    void Initialize() override
    {
        Batch2D::Initialize();

        Renderer::SetViewport(0.0f, 0.0f, 1280.0f, 720.0f);
        m_Camera = CreateRef<Camera2D>(1280.0f, 720.0f, 5.0f);

        m_DiamondTexture = Texture2D::Create("assets/textures/diamond.png");
        m_DiamondHoeTexture = Texture2D::Create("assets/textures/diamond_hoe.png");

        Batch2D::SetCamera(m_Camera);
    }

    void Update(float deltaTime) override
    {
        Renderer::SetClearColor(Colors::NICE_DARK_BLUE);
        Renderer::Clear();

        Batch2D::BeginBatch();

        Batch2D::PushQuad({-2.0f, 0.0f}, {1.0f, 1.0f}, m_DiamondTexture);
        Batch2D::PushQuad({2.0f, 0.0f}, {1.0f, 1.0f}, m_DiamondHoeTexture);

        Batch2D::EndBatch();
    }

private:
    Ref<Camera2D> m_Camera;
    Ref<Texture2D> m_DiamondTexture;
    Ref<Texture2D> m_DiamondHoeTexture;
};

Application* Thermo::CreateDefaultApplication()
{
    ApplicationSpecification spec;
    spec.WindowWidth = 1280;
    spec.WindowHeight = 720;
    spec.WindowTitle = "Thermo Editor";

    auto* app = new Application(spec);
    app->PushSystem<TestingSystem>();

    return app;
}