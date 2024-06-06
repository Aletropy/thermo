#define THERMO_ENTRY_POINT
#include <Thermo.h>

using namespace Thermo;

class TestingSystem : public System
{
public:

    void Initialize() override
    {
        Batch2D::Initialize();
    }

    void Update(float deltaTime) override
    {
        Renderer::SetClearColor(Colors::NICE_DARK_BLUE);
;       Renderer::Clear();

        Batch2D::BeginBatch();

        Batch2D::PushQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, Colors::LIME);

        Batch2D::EndBatch();
    }
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