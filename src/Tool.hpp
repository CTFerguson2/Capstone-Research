#pragma once

#include <SFML/Graphics.hpp>

enum class Tool {
    None,
    Brush,
    Eraser,
    Eyedropper,
    FillBucket
};

struct ToolState {
    Tool current = Tool::Brush;
    sf::Color brushColor = sf::Color::Black;
    float brushSize = 8.0f;
    float eraserSize = 20.0f;
};