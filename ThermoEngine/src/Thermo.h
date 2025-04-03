#ifndef THERMO_THERMO_H
#define THERMO_THERMO_H

#include "Core/Logger.h"
#include "Core/Base.h"
#include "Core/Keys.h"
#include "Core/Input.h"

#include "Events/Event.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

#include "Layers/ImGuiLayer.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"

#include "Application/Application.h"
#include "Application/EntryPoint.h"

#include "Graphics/Window.h"
#include "Graphics/Colors.h"
#include "Graphics/OrthographicCamera.h"
#include "Graphics/PerspectiveCamera.h"

#include "Graphics/Rendering/Texture/Texture2D.h"
#include "Graphics/Rendering/Texture/Spritesheet.h"
#include "Graphics/Rendering/Texture/SubTexture2D.h"

#include "Graphics/Rendering/Buffer/VertexBuffer.h"
#include "Graphics/Rendering/Buffer/VertexBuffer.h"
#include "Graphics/Rendering/Buffer/IndexBuffer.h"
#include "Graphics/Rendering/Framebuffer.h"
#include "Graphics/Rendering/Shader.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Rendering/Batch2D.h"

#include "ECS/EntityManager.h"
#include "ECS/ISystem.h"
#include "ECS/SystemManager.h"
#include "ECS/DefaultComponents/TransformComponent.h"
#include "ECS/DefaultComponents/NameComponent.h"
#include "ECS/DefaultComponents/QuadRendererComponent.h"


#ifdef THERMO_INCLUDE_SERIALIZATION
#include "ECS/Serialization/IComponentSerializer.h"
#include "ECS/Serialization/SerializerRegistry.h"
#endif


#endif //THERMO_THERMO_H
