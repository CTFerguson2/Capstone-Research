#include "App.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
namespace {
sf::Color colorFromFloats(const float color[4]) {
    return sf::Color(
        static_cast<std::uint8_t>(std::clamp(color[0], 0.0f, 1.0f) * 255.0f),
        static_cast<std::uint8_t>(std::clamp(color[1], 0.0f, 1.0f) * 255.0f),
        static_cast<std::uint8_t>(std::clamp(color[2], 0.0f, 1.0f) * 255.0f),
        static_cast<std::uint8_t>(std::clamp(color[3], 0.0f, 1.0f) * 255.0f)
    );
}
}

App::App()
    : window(sf::VideoMode(Constants::WINDOW_DIM), "Capstone Research"),
    deltaClock(){
        window.setFramerateLimit(60);
        if(!ImGui::SFML::Init(window)){
            std::cerr << "Failed to initialize ImGui";
        };
    }
//       canvas(800u, 600u) {
//     window.setFramerateLimit(60);
//     ImGui::SFML::Init(window);
// }

App::~App(){
    ImGui::SFML::Shutdown();
}

void App::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render();
    }
}


void App::processEvents(){
    while(const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        
        if(event -> is<sf::Event::Closed>())
            window.close();
    }
}

void App::update(){
    ImGui::SFML::Update(window, deltaClock.restart());
}

void App::render(){
    window.clear(Constants::BG_COLOR);
    ImGui::SFML::Render(window);
    window.display();
}



