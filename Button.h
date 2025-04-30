#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <concepts>

// ����� ������ ��� SFML. ����������� �� sf::Drawable 
// � sf::Transformable ��� ��������� � �������������.
class Button : public sf::Drawable, public sf::Transformable {

public:
    // ����������� ������ � ������ ������� ����������
    Button(std::wstring text, sf::Vector2f position, sf::Font& font,
        sf::Color buttonColor, sf::Color pressedColor,
        sf::Color textColor, sf::Color pressedTextColor,
        float width, float height, unsigned int fontSize,
        sf::Color outlineColor, float outlineThickness);

    // ������������ � ��������� �����������/�����������
    Button(const Button&) = default;
    Button& operator=(const Button&) = default;
    Button(Button&&) noexcept;
    Button& operator=(Button&&) noexcept;

    // ��������� ������ �� ������
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // ��������, ��� �� ���� �� ������
    [[nodiscard]] bool isClicked(sf::Vector2f mousePos) const noexcept;

    // ��������� ���������� ������ ������
    [[nodiscard]] sf::FloatRect getGlobalBounds() const noexcept;

    // ��������� ������ ������
    void setText(std::wstring text) noexcept;

    // �������� ��� �������
    void pressAnimation() noexcept;

    // �������� ��� ����������
    void releaseAnimation() noexcept;

    // ��������� ����� ������ (� �������������� concepts C++20)
    template<typename T> requires std::same_as<T, sf::Color>
    void setButtonColor(T color) noexcept;

    // ��������� ��������� ������
    void setPressedColor(sf::Color color) noexcept;
    void setTextColor(sf::Color color) noexcept;
    void setPressedTextColor(sf::Color color) noexcept;
    void setSize(float width, float height) noexcept;
    void setFontSize(unsigned int size) noexcept;
    void setBackgroundTransparency(unsigned int alpha) noexcept;
    void setOutlineColor(sf::Color color) noexcept;
    void setOutlineThickness(float thickness) noexcept;

    // ������������ ��������� (spaceship operator)
    auto operator<=>(const Button& other) const = default;

private:
    // ������������� ����� ������ � �����
    sf::RectangleShape shape;
    sf::Text label;

    // �����: �������, ��� �������, ��� ������ � ��� ������� ������
    sf::Color buttonColor;
    sf::Color pressedColor;
    sf::Color textColor;
    sf::Color pressedTextColor;

    // ������������ ���������: ������� ������� � ������ ������
    float originalOutlineThickness;
    unsigned int originalFontSize;

    // ���������� ������� ������ �� ������ ������
    void updateTextPosition() noexcept;
};