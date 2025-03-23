
#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <string>

class ColorfulText {
private:
    std::vector<sf::Text> letters;
    sf::Font& font;
    float colorTimer;
    static constexpr float COLOR_CHANGE_INTERVAL = 0.3f;

    void updateColors();

public:
    ColorfulText(sf::Font& font_ref, const std::wstring& text, unsigned int charSize,
        const sf::Vector2f& position, const sf::RenderWindow& window,
        bool centerHorizontally = false, bool centerVertically = false);

    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(const sf::Vector2f& position, bool centerHorizontally = false, bool centerVertically = false);
};