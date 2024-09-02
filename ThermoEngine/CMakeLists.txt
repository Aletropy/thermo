cmake_minimum_required(VERSION 3.1...3.29)
set(CMAKE_CXX_STANDARD 20)

project(ThermoEngine LANGUAGES CXX)

add_library(ThermoEngine STATIC
        src/Thermo.h

        src/Core/Logger.h
        src/Core/Logger.cpp
        src/Graphics/Window.cpp
        src/Graphics/Window.h
        src/Application/EntryPoint.h
        src/Graphics/Rendering/Renderer.cpp
        src/Graphics/Rendering/Renderer.h
        src/Core/Base.h
        src/Graphics/Colors.h
        src/Application/Application.cpp
        src/Application/Application.h
        src/Graphics/Rendering/Buffer/VertexBuffer.cpp
        src/Graphics/Rendering/Buffer/VertexBuffer.h
        src/Graphics/Rendering/Buffer/IndexBuffer.cpp
        src/Graphics/Rendering/Buffer/IndexBuffer.h
        src/Graphics/Rendering/Buffer/VertexArray.cpp
        src/Graphics/Rendering/Buffer/VertexArray.h
        src/Graphics/Rendering/Shader.cpp
        src/Graphics/Rendering/Shader.h
        src/ECS/System.h
        src/ECS/SystemManager.cpp
        src/ECS/SystemManager.h
        src/Graphics/Rendering/Batch2D.cpp
        src/Graphics/Rendering/Batch2D.h
        src/Graphics/Camera2D.cpp
        src/Graphics/Camera2D.h
        src/Core/Time.cpp
        src/Core/Time.h
        src/Memory/SparseSet.cpp
        src/Memory/SparseSet.h
        src/ECS/EntityManager.cpp
        src/ECS/EntityManager.h
        src/ECS/Systems/ImGuiSystem.cpp
        src/ECS/Systems/ImGuiSystem.h
        src/Graphics/Rendering/Texture2D.cpp
        src/Graphics/Rendering/Texture2D.h
        vendor/stb/stb_image.h
)

target_precompile_headers(ThermoEngine PRIVATE src/ThermoPch.h)

target_include_directories(ThermoEngine
        PUBLIC src
        PRIVATE vendor/stb
)

target_link_libraries(ThermoEngine
        PRIVATE glfw ThermoGlad
        PUBLIC glm imgui
)