#define THERMO_ENTRY_POINT
#include <Thermo.h>

using namespace Thermo;

class TestingSystem : public System
{
public:

    void Initialize() override
    {

        static const glm::vec4 vertices[] = {
                { -0.5f, -0.5f, 0.0f, 1.0f },
                { -0.5f, 0.5f, 0.0f, 1.0f },
                { 0.5f, 0.5f, 0.0f, 1.0f },
                { 0.5f, -0.5f, 0.0f, 1.0f }
        };

        const uint32_t indices[] = {
                0, 1, 2, 2, 3, 0
        };

        Vb = std::make_shared<VertexBuffer>(sizeof(vertices), (void*)vertices);

        Ib = std::make_shared<IndexBuffer>(sizeof(indices), (void*)indices);

        Vao = std::make_shared<VertexArray>();

        VertexLayout layout;
        layout.PushFloat(4);
        Vao->AddVertexBuffer(Vb, layout);
        Vao->SetIndexBuffer(Ib);

        ShaderProgram = std::make_shared<Shader>("assets/defaultShader.vert", "assets/defaultShader.frag");
    }

    void Update(float deltaTime) override
    {
        Renderer::SetClearColor(Colors::NICE_DARK_BLUE);
;       Renderer::Clear();

        ShaderProgram->Bind();
        Renderer::DrawIndexed(Vao, 6);
    }
private:
    Ref<VertexBuffer> Vb;
    Ref<IndexBuffer> Ib;
    Ref<Shader> ShaderProgram;
    Ref<VertexArray> Vao;
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