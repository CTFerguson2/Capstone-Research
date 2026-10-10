#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "App.hpp"
// const sf::Vector2u WINDOW_DIM = {800, 800};
// int main() {
//     sf::RenderWindow window(sf::VideoMode(WINDOW_DIM), "Capstone Research", sf::Style::Default, sf::State::Windowed);
//     if(! ImGui::SFML::Init(window)){
//         std::cerr << "ImGui initialization failed.\n";
//         return 1;
//     };
    
//     bool circleExists = true;
//     float circleRadius = 100.f;
//     sf::CircleShape shape(circleRadius, circleRadius);
//     shape.setFillColor(sf::Color(204, 77, 5));
//     shape.setPosition({(WINDOW_DIM.x) / 2.f - circleRadius, (WINDOW_DIM.y) / 2.f - circleRadius});

//     sf::RenderTexture canvas({500, 500});

//     float canvasZoom = 1.0f;
//     const float minZoom = 0.25f;
//     const float maxZoom = 8.0f;
    
//     sf::Clock deltaClock;

//     while(window.isOpen())
//     {
//         while(const std::optional event = window.pollEvent())
//         {
//             ImGui::SFML::ProcessEvent(window, *event);
//             if(event -> is<sf::Event::Closed>())
//                 window.close();
//             // else if (const auto* resized = event->getIf<sf::Event::Resized>())
//             // {
//             //     sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
//             //     window.setView(sf::View(visibleArea));
//             // }
//         }
//         ImGui::SFML::Update(window, deltaClock.restart());

//         ImGui::Begin("Window title");
//         ImGui::Text("Window text");
//         ImGui::Checkbox("Circle", &circleExists);
//         ImGui::SliderFloat("Circle radius", &circleRadius, 100.f, 300.f);
//         ImGui::End();

//         ImGui::Begin("Canvas");
//         ImGui::SliderFloat("Zoom", &canvasZoom, 0.25f, 8.0f);

//         if (ImGui::Button("100%")) {
//             canvasZoom = 1.0f;
//         }

//         ImGui::Separator();

//         ImGui::BeginChild(
//             "CanvasView",
//             ImVec2(0, 0),
//             true,
//             ImGuiWindowFlags_HorizontalScrollbar
//         );
//         canvas.clear(sf::Color::White);
//         // draw stuff to texture
//         canvas.display();
//         sf::Sprite sprite(canvas.getTexture());
//         window.draw(sprite);
//         sf::Vector2u canvasSize = canvas.getSize();

//         sf::Vector2f displaySize(
//             canvasSize.x * canvasZoom,
//             canvasSize.y * canvasZoom
//         );

//         ImVec2 imageTopLeft = ImGui::GetCursorScreenPos();

//         ImGui::Image(canvas.getTexture(), displaySize);

//         bool canvasHovered = ImGui::IsItemHovered();

//         ImGui::EndChild();
//         ImGui::End();

//         shape.setRadius(circleRadius);
//         shape.setPosition({(WINDOW_DIM.x) / 2.f - circleRadius, (WINDOW_DIM.y) / 2.f - circleRadius});
//         window.clear(sf::Color(18, 33, 43));
        
        
//         // sprite.setOrigin({250.f, 250.f});
//         // sprite.setPosition({WINDOW_DIM.x / 2.f, WINDOW_DIM.y / 2.f});
     

//         if(circleExists)
//             window.draw(shape);
        
//         ImGui::SFML::Render(window); // Render ImGui stuff
//         window.display();
//     }
//     ImGui::SFML::Shutdown();
//     return 0;
// }

int main(){
    App app;
    app.run();
    return 0;
}
