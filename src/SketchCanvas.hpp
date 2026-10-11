#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>

class SketchCanvas {
public:
    SketchCanvas(unsigned int width, unsigned int height);

    void drawBrush(sf::Vector2f from, sf::Vector2f to, float radius, sf::Color color);
    sf::Color pickColor(sf::Vector2u point) const;
    void fill(sf::Vector2u startPoint, sf::Color fillColor);
    void clear();

    const sf::Texture& getTexture() const;
    sf::Vector2u getSize() const;
    const sf::RenderTexture& getRenderTexture() const;
    bool exportPng(const std::filesystem::path& path) const;

private:
    void drawStroke(sf::Vector2f from, sf::Vector2f to, float radius, sf::Color color);

    sf::RenderTexture renderTexture;
    sf::Color backgroundColor = sf::Color::White;
};