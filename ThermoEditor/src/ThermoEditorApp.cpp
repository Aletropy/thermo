#define THERMO_ENTRY_POINT
#include <iostream>
#include <filesystem>
#include <Thermo.h>

#include "SceneLayer.h"
#include "EditorLayer.h"
#include "PathHelper.h"
#include "Core/Project.h"

Application *Thermo::CreateDefaultApplication(const int argc, char *argv[])
{
    WindowAppSpecification spec;

    spec.WindowWidth = WIDTH;
    spec.WindowHeight = HEIGHT;
    spec.WindowTitle = "Thermo Editor";

    if (argc < 2)
    {
        THERMO_ERROR("Expected project filepath as argument.", 0);
        std::exit(1);
    }

    const auto projectPath = std::filesystem::path(argv[1]);

    if (!projectPath.is_absolute())
    {
        THERMO_ERROR("Project path must be absolute.", 0);
        std::exit(1);
    }

    ThermoEditor::PathHelper::StartAtPath(projectPath);

    ThermoEditor::Project::Instance = ThermoEditor::Project::LoadOrCreateProject(projectPath);

    auto *app = new Application(spec);

    app->ChangeWindowName("Thermo Editor | " + ThermoEditor::Project::Instance.GetProjectName());

    // Rendering and processing systems
    const auto sceneLayer = app->PushLayer<ThermoEditor::SceneLayer>();

    // Editor UI
    app->PushOverlay<ThermoEditor::EditorLayer>(
        sceneLayer->GetEditorCamera(),
        sceneLayer->GetEditorCameraPerspective(),
        sceneLayer->GetFramebuffer()
    );

    return app;
}
