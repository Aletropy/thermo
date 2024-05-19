#include <Thermo.h>

using namespace Thermo;

int main()
{
    Window window(800, 600, "Minha Janela");

    while(!window.IsClosed())
    {
        window.UpdateWindow();
    }

    return 0;
}