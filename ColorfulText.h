#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <memory>

class ColorfulText {
public:
    ColorfulText(const std::string& fontId, std::wstring_view text, unsigned int charSize,
        const sf::Vector2f& position, const sf::RenderWindow& window,
        bool centerHorizontally = false, bool centerVertically = false);

    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const;

    void setPosition(const sf::Vector2f& position,
        bool centerHorizontally = false,
        bool centerVertically = false);

private:
    void updateColors();

    std::shared_ptr<sf::Font> font;
    std::vector<sf::Text> letters;
    float colorTimer;
    static constexpr float COLOR_CHANGE_INTERVAL = 0.5f;
};