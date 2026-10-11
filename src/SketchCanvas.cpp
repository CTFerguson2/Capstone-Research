#include "SketchCanvas.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

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

sf::Color SketchCanvas::pickColor(sf::Vector2u point) const {
    sf::Vector2u size = renderTexture.getSize();

    if (point.x >= size.x || point.y >= size.y) {
        return sf::Color::Transparent;
    }

    sf::Image image = renderTexture.getTexture().copyToImage();

    return image.getPixel(point);
}

void SketchCanvas::fill(sf::Vector2u startPoint, sf::Color fillColor) {
    sf::Vector2u size = renderTexture.getSize();

    if (startPoint.x >= size.x || startPoint.y >= size.y) {
        return;
    }

    sf::Image image = renderTexture.getTexture().copyToImage();
    sf::Color targetColor = image.getPixel(startPoint);

    if (targetColor == fillColor) {
        return;
    }

    std::vector<sf::Vector2u> pixels;
    pixels.push_back(startPoint);

    while (!pixels.empty()) {
        sf::Vector2u point = pixels.back();
        pixels.pop_back();

        if (point.x >= size.x || point.y >= size.y) {
            continue;
        }

        if (image.getPixel(point) != targetColor) {
            continue;
        }

        image.setPixel(point, fillColor);

        if (point.x > 0) {
            pixels.push_back({point.x - 1, point.y});
        }

        if (point.x + 1 < size.x) {
            pixels.push_back({point.x + 1, point.y});
        }

        if (point.y > 0) {
            pixels.push_back({point.x, point.y - 1});
        }

        if (point.y + 1 < size.y) {
            pixels.push_back({point.x, point.y + 1});
        }
    }

    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        return;
    }

    sf::Sprite sprite(texture);

    renderTexture.clear();
    renderTexture.draw(sprite);
    renderTexture.display();
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