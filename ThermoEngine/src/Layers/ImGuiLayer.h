#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"

namespace Thermo
{
    class ImGuiLayer : public Layer
    {
    public:
        void OnAttach() override;

        static void Start();
        static void End();

    private:
        static void SetupStyle();
    };
}

#endif //IMGUILAYER_H
