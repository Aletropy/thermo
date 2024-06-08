#define THERMO_ENTRY_POINT
#include <Thermo.h>

using namespace Thermo;

class TestingSystem : public System
{
public:
    void Initialize() override
    {
        Batch2D::Initialize();

        Renderer::SetViewport(0.0f, 0.0f, 800.0f, 600.0f);
        m_Camera = CreateRef<Camera2D>(800.0f, 600.0f, 5.0f);

        Batch2D::SetCamera(m_Camera);
    }

    void Update(float deltaTime) override
    {
        Renderer::SetClearColor(Colors::NICE_DARK_BLUE);
        Renderer::Clear();
    }
private:
    Ref<Camera2D> m_Camera;
};

Application* Thermo::CreateDefaultApplication()
{
    ApplicationSpecification spec;
    spec.WindowWidth = 800;
    spec.WindowHeight = 600;
    spec.WindowTitle = "Sandbox Window";

    auto* app = new Application(spec);
    app->PushSystem<TestingSystem>();

    return app;
}