#pragma once

#include <SFML/Graphics.hpp>

class SketchCanvas {
public:
    SketchCanvas(unsigned int width, unsigned int height);

    void drawBrush(sf::Vector2f from, sf::Vector2f to, float radius, sf::Color color);
    void erase(sf::Vector2f from, sf::Vector2f to, float radius);
    void clear();

    const sf::Texture& getTexture() const;
    sf::Vector2u getSize() const;
    const sf::RenderTexture& getRenderTexture() const;

private:
    void drawStroke(sf::Vector2f from, sf::Vector2f to, float radius, sf::Color color);

    sf::RenderTexture renderTexture;
    sf::Color backgroundColor = sf::Color::White;
};