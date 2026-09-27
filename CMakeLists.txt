cmake_minimum_required(VERSION 3.24)

project(CapstoneResearch LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(capstone-research
    src/main.cpp
)

target_compile_features(capstone-research PRIVATE cxx_std_20)

target_link_libraries(capstone-research PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)