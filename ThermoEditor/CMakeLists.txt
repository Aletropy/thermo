cmake_minimum_required(VERSION 3.1...3.29)

set(CMAKE_CXX_STANDARD 20)

project(ThermoEditor LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ThermoEditor
        src/ThermoEditorApp.cpp
)

target_include_directories(ThermoEditor PRIVATE src)

target_link_libraries(ThermoEditor PRIVATE ThermoEngine)