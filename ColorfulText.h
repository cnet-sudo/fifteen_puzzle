
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>

class ColorfulText {
private:
    sf::Font* font;  // ”казатель на шрифт из ResourceManager
    std::vector<sf::Text> letters;
    float colorTimer;
    static constexpr float COLOR_CHANGE_INTERVAL = 0.5f; // »нтервал смены цвета

    void updateColors();

public:
    ColorfulText(const std::string& fontId, const std::wstring& text, unsigned int charSize,
        const sf::Vector2f& position, const sf::RenderWindow& window,
        bool centerHorizontally = false, bool centerVertically = false);

    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(const sf::Vector2f& position, bool centerHorizontally = false, bool centerVertically = false);
};