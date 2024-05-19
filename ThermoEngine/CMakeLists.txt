cmake_minimum_required(VERSION 3.1...3.29)
set(CMAKE_CXX_STANDARD 20)

project(ThermoEngine LANGUAGES CXX)

add_library(ThermoEngine STATIC
        src/Thermo.h

        src/Core/Logger.h
        src/Core/Logger.cpp
        src/Graphics/Window.cpp
        src/Graphics/Window.h
)

target_precompile_headers(ThermoEngine PRIVATE src/ThermoPch.h)

target_include_directories(ThermoEngine PUBLIC src)

target_link_libraries(ThermoEngine
        PRIVATE glfw ThermoGlad
)