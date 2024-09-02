#ifndef THERMOENGINE_WINDOW_H
#define THERMOENGINE_WINDOW_H

struct GLFWwindow;

#include <string>

namespace Thermo
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void UpdateWindow();
        bool IsClosed() const;

        GLFWwindow* GetHandle() const { return m_Window; }

    private:
        GLFWwindow* m_Window;
    };

} // Thermo

#endif //THERMOENGINE_WINDOW_H
