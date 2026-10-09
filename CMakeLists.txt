cmake_minimum_required(VERSION 3.24)

project(CapstoneResearch LANGUAGES CXX)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

add_executable(capstone-research
    src/main.cpp
)

target_compile_features(capstone-research PRIVATE cxx_std_20)

target_link_libraries(capstone-research PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    ImGui-SFML::ImGui-SFML
)