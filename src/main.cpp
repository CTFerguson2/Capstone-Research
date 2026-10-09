#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>


int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Capstone Research");
    if(! ImGui::SFML::Init(window)){
        std::cerr << "ImGui initialization failed.\n";
        return 1;
    };
    
    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color(204, 77, 5));
    shape.setPosition({200, 200});

    sf::Clock deltaClock;

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if(event -> is<sf::Event::Closed>())
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window title");
        ImGui::Text("Window text");
        ImGui::End();

        window.clear(sf::Color(18, 33, 43));
        window.draw(shape);

        ImGui::SFML::Render(window); // Render ImGui stuff
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
