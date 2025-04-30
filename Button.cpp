#include "Button.h"
#include <ranges>

// Конструктор с параметрами
Button::Button(std::wstring text, sf::Vector2f position, sf::Font& font,
    sf::Color buttonColor, sf::Color pressedColor, sf::Color textColor,
    sf::Color pressedTextColor, float width, float height, unsigned int fontSize,
    sf::Color outlineColor, float outlineThickness)
    : buttonColor{ buttonColor },
    pressedColor{ pressedColor },
    textColor{ textColor },
    pressedTextColor{ pressedTextColor },
    originalOutlineThickness{ outlineThickness },
    originalFontSize{ fontSize }
{
    shape.setSize(sf::Vector2f{ width, height });
    shape.setFillColor(buttonColor);
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(outlineThickness);
    shape.setPosition(position);

    label.setFont(font);
    label.setString(std::move(text));
    label.setCharacterSize(fontSize);
    label.setFillColor(textColor);

    updateTextPosition();
}

// Центрирует текст по центру кнопки
void Button::updateTextPosition() noexcept {
    const auto textBounds = label.getLocalBounds();
    label.setOrigin({
        textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f
        });

    const auto shapePos = shape.getPosition();
    const auto shapeSize = shape.getSize();
    label.setPosition({
        shapePos.x + shapeSize.x / 2.0f,
        shapePos.y + shapeSize.y / 2.0f
        });
}

// Проверка попадания курсора мыши в границы кнопки
[[nodiscard]] bool Button::isClicked(sf::Vector2f mousePos) const noexcept {
    return shape.getGlobalBounds().contains(mousePos);
}

// Устанавливает новый текст
void Button::setText(std::wstring text) noexcept {
    label.setString(std::move(text));
    updateTextPosition();
}

// Визуальная анимация при нажатии на кнопку
void Button::pressAnimation() noexcept {
    shape.setFillColor(pressedColor);
    label.setFillColor(pressedTextColor);
    shape.setOutlineThickness(1.0f); // уменьшаем толщину обводки
    label.setCharacterSize(originalFontSize - 2); // уменьшаем размер текста
    updateTextPosition();
}

// Визуальная анимация при отпускании кнопки
void Button::releaseAnimation() noexcept {
    shape.setFillColor(buttonColor);
    label.setFillColor(textColor);
    shape.setOutlineThickness(originalOutlineThickness);
    label.setCharacterSize(originalFontSize);
    updateTextPosition();
}

// Установка цвета кнопки (через шаблон с concept)
template<typename T>
    requires std::same_as<T, sf::Color>
void Button::setButtonColor(T color) noexcept {
    this->buttonColor = color;
    shape.setFillColor(color);
}

// Установка цвета при нажатии
void Button::setPressedColor(sf::Color color) noexcept {
    this->pressedColor = color;
}

// Установка цвета текста
void Button::setTextColor(sf::Color color) noexcept {
    this->textColor = color;
    label.setFillColor(color);
}

// Установка цвета текста при нажатии
void Button::setPressedTextColor(sf::Color color) noexcept {
    this->pressedTextColor = color;
}

// Изменение размера кнопки
void Button::setSize(float width, float height) noexcept {
    shape.setSize({ width, height });
    updateTextPosition();
}

// Изменение размера шрифта
void Button::setFontSize(unsigned int size) noexcept {
    originalFontSize = size;
    label.setCharacterSize(size);
    updateTextPosition();
}

// Установка прозрачности фона кнопки
void Button::setBackgroundTransparency(unsigned int alpha) noexcept {
    buttonColor.a = static_cast<std::uint8_t>(std::clamp(alpha, 0u, 255u));
    shape.setFillColor(buttonColor);
}

// Установка цвета обводки
void Button::setOutlineColor(sf::Color color) noexcept {
    shape.setOutlineColor(color);
}

// Установка толщины обводки
void Button::setOutlineThickness(float thickness) noexcept {
    originalOutlineThickness = thickness;
    shape.setOutlineThickness(thickness);
}

// Отрисовка кнопки и текста
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    target.draw(shape, states);
    target.draw(label, states);
}

// Получение границ кнопки (для коллизий/кликов)
[[nodiscard]] sf::FloatRect Button::getGlobalBounds() const noexcept {
    return shape.getGlobalBounds();
}

// Конструктор перемещения
Button::Button(Button&& other) noexcept = default;

// Оператор перемещения
Button& Button::operator=(Button&& other) noexcept = default;
