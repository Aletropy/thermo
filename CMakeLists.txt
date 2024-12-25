cmake_minimum_required(VERSION 3.1...3.29)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

project(ThermoGlad)
project(glfw)
project(glm)
project(imgui)

project(ThermoEditor)
project(ThermoEngine)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/thermo-glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)

add_subdirectory(ThermoEngine)
add_subdirectory(ThermoEditor)
