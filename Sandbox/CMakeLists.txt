cmake_minimum_required(VERSION 3.1...3.29)

set(CMAKE_CXX_STANDARD 20)

project(Sandbox LANGUAGES CXX)

add_executable(Sandbox
        src/SandboxApp.cpp
)

target_include_directories(Sandbox PRIVATE src)

target_link_libraries(Sandbox PRIVATE ThermoEngine)