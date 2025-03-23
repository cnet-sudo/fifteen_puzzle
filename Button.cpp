#include "Button.h"

Button::Button(const std::wstring& text, sf::Vector2f position, sf::Font& font,
    sf::Color buttonColor, sf::Color pressedColor, sf::Color textColor,
    sf::Color pressedTextColor, float width, float height, unsigned int fontSize,
    sf::Color outlineColor, float outlineThickness)
    : buttonColor(buttonColor), pressedColor(pressedColor), textColor(textColor), pressedTextColor(pressedTextColor),
    originalOutlineThickness(outlineThickness), originalFontSize(fontSize) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(buttonColor);
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(outlineThickness);
    shape.setPosition(position);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(fontSize);
    label.setFillColor(textColor);

    updateTextPosition();
}

void Button::updateTextPosition() {
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    label.setPosition(shape.getPosition().x + shape.getSize().x / 2.0f,
        shape.getPosition().y + shape.getSize().y / 2.0f);
}

bool Button::isClicked(sf::Vector2f mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::setText(const std::wstring& text) {
    label.setString(text);
    updateTextPosition();
}

void Button::pressAnimation() {
    shape.setFillColor(pressedColor);
    label.setFillColor(pressedTextColor);
    shape.setOutlineThickness(1.0f);
    label.setCharacterSize(originalFontSize - 2);
    updateTextPosition();
}

void Button::releaseAnimation() {
    shape.setFillColor(buttonColor);
    label.setFillColor(textColor);
    shape.setOutlineThickness(originalOutlineThickness);
    label.setCharacterSize(originalFontSize);
    updateTextPosition();
}

void Button::setButtonColor(sf::Color color) {
    buttonColor = color;
    shape.setFillColor(buttonColor);
}

void Button::setPressedColor(sf::Color color) {
    pressedColor = color;
}

void Button::setTextColor(sf::Color color) {
    textColor = color;
    label.setFillColor(textColor);
}

void Button::setPressedTextColor(sf::Color color) {
    pressedTextColor = color;
}

void Button::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    updateTextPosition();
}

void Button::setFontSize(unsigned int size) {
    originalFontSize = size;
    label.setCharacterSize(size);
    updateTextPosition();
}

void Button::setBackgroundTransparency(unsigned int alpha) {
    buttonColor.a = alpha;
    shape.setFillColor(buttonColor);
}

void Button::setOutlineColor(sf::Color color) {
    shape.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    originalOutlineThickness = thickness;
    shape.setOutlineThickness(thickness);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
    target.draw(label, states);
}

sf::FloatRect Button::getGlobalBounds() const {
    return shape.getGlobalBounds();
}
