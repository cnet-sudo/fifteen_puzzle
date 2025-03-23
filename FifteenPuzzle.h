#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <string>

class FifteenPuzzle : public sf::Drawable {
public:
    static constexpr int DEFAULT_TILE_SIZE = 100;
    static constexpr int DEFAULT_GRID_SIZE = 4;

    explicit FifteenPuzzle(int tileSize = DEFAULT_TILE_SIZE,
        int gridSize = DEFAULT_GRID_SIZE);
    ~FifteenPuzzle() = default;

    // Delete copy constructor and assignment operator
    FifteenPuzzle(const FifteenPuzzle&) = delete;
    FifteenPuzzle& operator=(const FifteenPuzzle&) = delete;

    // Move constructor and assignment operator
    FifteenPuzzle(FifteenPuzzle&&) = default;
    FifteenPuzzle& operator=(FifteenPuzzle&&) = default;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update();
    bool isSolved() const;
    void restart();

private:
    const int m_tileSize;
    const int m_gridSize;
    std::vector<std::vector<int>> m_board;
    std::unique_ptr<sf::Font> m_font;
    int m_emptyX, m_emptyY;
    sf::Vector2f m_position;
    bool m_isSolved;

    void shuffleBoard();
    bool canMove(int x, int y) const;
    void moveTile(int x, int y);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



