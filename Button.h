#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable {
public:
    Button(const std::wstring& text, sf::Vector2f position, sf::Font& font,
        sf::Color buttonColor, sf::Color pressedColor, sf::Color textColor,
        sf::Color pressedTextColor, float width, float height, unsigned int fontSize,
        sf::Color outlineColor, float outlineThickness);

    bool isClicked(sf::Vector2f mousePos) const;
    void setText(const std::wstring& text);
    void pressAnimation();
    void releaseAnimation();
    void setButtonColor(sf::Color color);
    void setPressedColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPressedTextColor(sf::Color color);
    void setSize(float width, float height);
    void setFontSize(unsigned int size);
    void setBackgroundTransparency(unsigned int alpha);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float thickness);
    void updateTextPosition();

    // Новый метод для получения глобальных границ кнопки
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Color buttonColor;
    sf::Color pressedColor;
    sf::Color textColor;
    sf::Color pressedTextColor;
    float originalOutlineThickness;
    unsigned int originalFontSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};