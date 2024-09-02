#ifndef IMGUISYSTEM_H
#define IMGUISYSTEM_H

#include "ECS/System.h"

namespace Thermo
{
    class ImGuiSystem : public System
    {
    public:
        void Initialize() override;

        static void Start();
        static void End();
    private:
        static void SetupStyle();
    };
}

#endif //IMGUISYSTEM_H
