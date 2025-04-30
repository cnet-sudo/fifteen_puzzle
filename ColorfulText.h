#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <memory>

// Класс ColorfulText — отображает анимированный разноцветный текст
class ColorfulText {
public:
    // Конструктор
    ColorfulText(const std::string& fontId, std::wstring_view text, unsigned int charSize,
        const sf::Vector2f& position, const sf::RenderWindow& window,
        bool centerHorizontally = false, bool centerVertically = false);

    // Обновление цвета текста (вызывается в цикле игры)
    void update(float deltaTime);

    // Отрисовка текста на экране
    void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const;

    // Установка новой позиции текста с возможностью центрирования
    void setPosition(const sf::Vector2f& position,
        bool centerHorizontally = false,
        bool centerVertically = false);

private:
    // Обновление цветов букв на случайные
    void updateColors();

    std::shared_ptr<sf::Font> font;       // Шрифт
    std::vector<sf::Text> letters;        // Вектор отдельных букв (sf::Text)
    float colorTimer;                     // Таймер для смены цвета
    static constexpr float COLOR_CHANGE_INTERVAL = 0.5f; // Интервал смены цвета
};
