class SketchCanvas {
public:
    SketchCanvas(unsigned int width, unsigned int height);

    void drawBrush(sf::Vector2f from, sf::Vector2f to, float radius, sf::Color color);
    void erase(sf::Vector2f from, sf::Vector2f to, float radius);
    void clear();

    sf::Color pickColor(sf::Vector2u point) const;
    void fill(sf::Vector2u point, sf::Color color);

    void undo();
    void redo();

    bool exportPng(const std::filesystem::path& path) const;

    const sf::Texture& getTexture() const;
    sf::Vector2u getSize() const;

private:
    sf::RenderTexture canvas;
    sf::Color background = sf::Color::White;

    std::vector<sf::Image> undoStack;
    std::vector<sf::Image> redoStack;

    void saveUndoSnapshot();
};