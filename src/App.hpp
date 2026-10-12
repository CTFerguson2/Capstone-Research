#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "SketchCanvas.hpp"
#include "Tool.hpp"
#include "UI.hpp"
#include <memory>

namespace Constants{
    inline constexpr const sf::Vector2u WINDOW_DIM = {1000, 700};
    inline constexpr const sf::Color BG_COLOR = sf::Color(194, 197, 204);
}

class App {

public:
    App();
    ~App();
    
    void run();

private:
    
    void processEvents();
    void update();
    void render();

    void drawCanvasPanel(); 

    sf::RenderWindow window;
    sf::Clock deltaClock;

    std::unique_ptr<SketchCanvas> canvas;
    ToolState tools;
    UI ui;
    
    float canvasZoom = 1.0f;

    bool isDrawing = false;
    sf::Vector2f lastCanvasPoint{};
};