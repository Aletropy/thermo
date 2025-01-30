#define THERMO_ENTRY_POINT
#include <Thermo.h>

#include "SceneLayer.h"
#include "EditorLayer.h"

Application *Thermo::CreateDefaultApplication()
{
    WindowAppSpecification spec;
    spec.WindowWidth = WIDTH;
    spec.WindowHeight = HEIGHT;
    spec.WindowTitle = "Thermo Editor";

    auto *app = new Application(spec);

    // Rendering and processing systems
    const auto sceneLayer = app->PushLayer<ThermoEditor::SceneLayer>();

    // Editor UI
    app->PushOverlay<ThermoEditor::EditorLayer>(
        sceneLayer->GetEditorCamera(),
        sceneLayer->GetEntityManager(),
        sceneLayer->GetFramebuffer()
    );

    return app;
}
