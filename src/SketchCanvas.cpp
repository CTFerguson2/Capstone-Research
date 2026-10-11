#include "SketchCanvas.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

SketchCanvas::SketchCanvas(unsigned int width, unsigned int height) {
    if (!renderTexture.resize({width, height})) {
        throw std::runtime_error("Failed to create canvas render texture.");
    }

    clear();
}

void SketchCanvas::drawBrush(
    sf::Vector2f from,
    sf::Vector2f to,
    float radius,
    sf::Color color
) {
    drawStroke(from, to, radius, color);
}

void SketchCanvas::clear() {
    renderTexture.clear(backgroundColor);
    renderTexture.display();
}

const sf::Texture& SketchCanvas::getTexture() const {
    return renderTexture.getTexture();
}

sf::Vector2u SketchCanvas::getSize() const {
    return renderTexture.getSize();
}

void SketchCanvas::drawStroke(
    sf::Vector2f from,
    sf::Vector2f to,
    float radius,
    sf::Color color
) {
    radius = std::max(radius, 1.0f);

    sf::Vector2f delta = to - from;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    int steps = std::max(1, static_cast<int>(distance / (radius * 0.5f)));

    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(steps);

        sf::Vector2f position = from + delta * t;

        sf::CircleShape brush(radius);
        brush.setFillColor(color);
        brush.setOrigin({radius, radius});
        brush.setPosition(position);

        renderTexture.draw(brush);
    }

    renderTexture.display();
}

const sf::RenderTexture& SketchCanvas::getRenderTexture() const {
    return renderTexture;
}