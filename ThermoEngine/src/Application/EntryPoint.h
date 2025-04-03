#ifndef THERMOENGINE_ENTRYPOINT_H
#define THERMOENGINE_ENTRYPOINT_H

#ifdef THERMO_ENTRY_POINT

#include "Application.h"

namespace Thermo
{
    extern Application *CreateDefaultApplication(int argc, char *argv[]);
}

int main(const int argc, char *argv[])
{
    const auto app = Thermo::CreateDefaultApplication(argc, argv);
    app->Run();
    delete app;
    return 0;
}

#endif // THERMO_ENTRY_POINT

#endif //THERMOENGINE_ENTRYPOINT_H
