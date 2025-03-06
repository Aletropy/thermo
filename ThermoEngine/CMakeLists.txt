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
        src/ECS/ISystem.h
        src/ECS/SystemManager.cpp
        src/ECS/SystemManager.h
        src/Graphics/Rendering/Batch2D.cpp
        src/Graphics/Rendering/Batch2D.h
        src/Graphics/OrthographicCamera.cpp
        src/Graphics/OrthographicCamera.h
        src/Core/Time.cpp
        src/Core/Time.h
        src/Memory/SparseSet.h
        src/Layers/ImGuiLayer.cpp
        src/Layers/ImGuiLayer.h
        src/Graphics/Rendering/Texture/Texture2D.cpp
        src/Graphics/Rendering/Texture/Texture2D.h
        vendor/stb/stb_image.h
        src/Graphics/Rendering/Framebuffer.cpp
        src/Graphics/Rendering/Framebuffer.h
        vendor/entt/entt.h
        src/ECS/EntityManager.cpp
        src/ECS/EntityManager.h
        src/Core/Layer.h
        src/Core/LayerStack.cpp
        src/Core/LayerStack.h
        src/Events/Event.h
        src/Events/WindowEvents.h
        src/Events/KeyboardEvents.h
        src/Events/MouseEvents.h
        src/ECS/DefaultComponents/TransformComponent.h
        src/ECS/DefaultComponents/QuadRendererComponent.h
        src/Graphics/PerspectiveCamera.cpp
        src/Graphics/PerspectiveCamera.h
        src/Graphics/Camera.h
        src/Graphics/Rendering/Texture/SubTexture2D.h
        src/Graphics/Rendering/Texture/Spritesheet.cpp
        src/Graphics/Rendering/Texture/Spritesheet.h
        src/Core/Keys.h
        src/Core/Input.cpp
        src/Core/Input.h
        src/ECS/DefaultComponents/NameComponent.h
        src/ECS/Components/EditorComponent.h
)

target_precompile_headers(ThermoEngine PRIVATE src/ThermoPch.h)

target_include_directories(ThermoEngine
        PUBLIC src vendor/entt
        PRIVATE vendor/stb
)

target_link_libraries(ThermoEngine
        PRIVATE glfw ThermoGlad
        PUBLIC glm ImGui
)