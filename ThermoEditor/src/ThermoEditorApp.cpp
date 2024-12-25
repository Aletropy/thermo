#define THERMO_ENTRY_POINT
#include <Thermo.h>
#include "MainLayer.h"

Application* Thermo::CreateDefaultApplication()
{
    WindowAppSpecification spec;
    spec.WindowWidth = WIDTH;
    spec.WindowHeight = HEIGHT;
    spec.WindowTitle = "Thermo Editor";

    auto* app = new Application(spec);
    app->PushLayer<ThermoEditor::MainLayer>();

    return app;
}