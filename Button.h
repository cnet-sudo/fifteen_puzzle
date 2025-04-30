#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <concepts>

// Класс кнопки для SFML. Наследуется от sf::Drawable 
// и sf::Transformable для отрисовки и трансформаций.
class Button : public sf::Drawable, public sf::Transformable {

public:
    // Конструктор кнопки с полным набором параметров
    Button(std::wstring text, sf::Vector2f position, sf::Font& font,
        sf::Color buttonColor, sf::Color pressedColor,
        sf::Color textColor, sf::Color pressedTextColor,
        float width, float height, unsigned int fontSize,
        sf::Color outlineColor, float outlineThickness);

    // Конструкторы и операторы копирования/перемещения
    Button(const Button&) = default;
    Button& operator=(const Button&) = default;
    Button(Button&&) noexcept;
    Button& operator=(Button&&) noexcept;

    // Отрисовка кнопки на экране
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Проверка, был ли клик по кнопке
    [[nodiscard]] bool isClicked(sf::Vector2f mousePos) const noexcept;

    // Получение глобальных границ кнопки
    [[nodiscard]] sf::FloatRect getGlobalBounds() const noexcept;

    // Установка текста кнопки
    void setText(std::wstring text) noexcept;

    // Анимация при нажатии
    void pressAnimation() noexcept;

    // Анимация при отпускании
    void releaseAnimation() noexcept;

    // Установка цвета кнопки (с использованием concepts C++20)
    template<typename T> requires std::same_as<T, sf::Color>
    void setButtonColor(T color) noexcept;

    // Остальные настройки кнопки
    void setPressedColor(sf::Color color) noexcept;
    void setTextColor(sf::Color color) noexcept;
    void setPressedTextColor(sf::Color color) noexcept;
    void setSize(float width, float height) noexcept;
    void setFontSize(unsigned int size) noexcept;
    void setBackgroundTransparency(unsigned int alpha) noexcept;
    void setOutlineColor(sf::Color color) noexcept;
    void setOutlineThickness(float thickness) noexcept;

    // Трёхстороннее сравнение (spaceship operator)
    auto operator<=>(const Button& other) const = default;

private:
    // Прямоугольная форма кнопки и текст
    sf::RectangleShape shape;
    sf::Text label;

    // Цвета: обычный, при нажатии, для текста и при нажатии текста
    sf::Color buttonColor;
    sf::Color pressedColor;
    sf::Color textColor;
    sf::Color pressedTextColor;

    // Оригинальные параметры: толщина границы и размер шрифта
    float originalOutlineThickness;
    unsigned int originalFontSize;

    // Обновление позиции текста по центру кнопки
    void updateTextPosition() noexcept;
};