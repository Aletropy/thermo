# 🔥 Thermo Engine

Thermo is a high-performance 2D rendering engine built with C++ and modern OpenGL. It implements an Entity-Component-System (ECS) architecture to handle thousands of entities efficiently. Features a custom Batch Renderer to minimize draw calls and optimize GPU usage.

## About The Project

Thermo is a personal project born out of a passion for understanding how game engines work under the hood. It is not intended for creating AAA titles, but rather to serve as a hands-on educational tool. The engine is being developed in **C++** and uses modern **OpenGL** for rendering.

The core philosophy is to build key systems from the ground up to gain a deep understanding of game architecture, rendering pipelines, and tool development.

**Core Technologies:**
*   **Language:** C++
*   **Graphics API:** OpenGL
*   **UI Library:** [Dear ImGui](https://github.com/ocornut/imgui) for the editor tools.
*   **Architecture:** Entity-Component-System (ECS) | [entt](https://github.com/skypjack/entt)

## ✅ Current Features

*   **2D Batch Renderer:** A simple but effective renderer for 2D sprites and shapes, powered by OpenGL.
*   **Entity-Component-System (ECS):** A modern, data-oriented architecture for flexible and scalable game object management.
*   **ImGui Editor:** A powerful, integrated editor for real-time scene manipulation.
*   **Scene Serialization:** Save and load entire scenes, including all entities and their components, to human-readable files (e.g., YAML).
*   **Basic Logging System:** For easy debugging and tracking engine events.

![image](https://raw.githubusercontent.com/Aletropy/thermo/refs/heads/development/docs/images/editor_screenshot.png)

## 🚀 Roadmap

This project is actively under development. Here are some of the major features planned for the future:

*   **Spritesheet & Animation System:** Support for 2D animations using spritesheets.
*   **Material System:** A basic system to define surface properties for rendered objects.
*   **Scripting:** Integrate a scripting language (e.g., Lua, or a custom one) to define game logic.
*   **Editor/Runtime Separation:** A clear distinction between the code that runs in the editor and the code that runs in the final game.
*   **Standalone Game Builds:** The ability to compile and export a game project into a distributable executable, without the editor.

## Getting Started

As this is a personal development project, the build process is subject to change. However, you can generally build the engine using CMake.

### Prerequisites

*   A C++ compiler (MSVC, GCC, Clang)
*   [CMake](https://cmake.org/)
*   [Git](https://git-scm.com/)
*   [Ninja](https://ninja-build.org/)

### Building

1.  Clone the repository:
    ```sh
    git clone --recursive https://github.com/aletropy/thermo.git
    cd thermo
    ```
3.  Generate the project files using CMake:
    ```sh
    cmake -B build
    ```
4.  Build the project:
    ```sh
    cd build
    ninja
    ```

## Contributing

This is primarily a personal learning project. Therefore, direct contributions are not the main focus. However, feel free to fork the repository, and if you have suggestions or find bugs, you are welcome to open an issue.

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## Acknowledgments

This project would not be possible without these incredible open-source libraries:

*   [Dear ImGui](https://github.com/ocornut/imgui)
*   [glad](https://github.com/Dav1dde/glad)
*   [GLFW](https://www.glfw.org/)
*   [entt](https://github.com/skypjack/entt)
*   [glm](https://github.com/g-truc/glm)
*   [stb](https://github.com/nothings/stb)
*   [yaml-cpp](https://github.com/jbeder/yaml-cpp)
