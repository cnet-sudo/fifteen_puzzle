// ColorfulText.cpp
#include "ColorfulText.h"
#include "ResourceManager.h"
#include <algorithm>
#include <random>

ColorfulText::ColorfulText(const std::string& fontId, std::wstring_view text, unsigned int charSize,
    const sf::Vector2f& position, const sf::RenderWindow& window,
    bool centerHorizontally, bool centerVertically)
    : colorTimer(0.0f) {

    // Получаем шрифт из ResourceManager по идентификатору
    ResourceManager& rm = ResourceManager::getInstance();
    font = std::make_shared<sf::Font>(rm.getFont(fontId));

    // Проверка шрифта
    if (font->getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт с ID: " + std::string(fontId) + " из ResourceManager");
    }

    // Рассчитываем позицию
    float totalWidth = text.size() * charSize * 0.8f;
    float xPos = position.x;
    float yPos = position.y;

    if (centerHorizontally) {
        xPos = (window.getSize().x - totalWidth) / 2.0f;
    }
    if (centerVertically) {
        yPos = (window.getSize().y - charSize) / 2.0f;
    }

    // Создаем буквы
    letters.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        sf::Text letter;
        letter.setFont(*font);
        letter.setString(text[i]);
        letter.setCharacterSize(charSize);
        letter.setFillColor(sf::Color::Magenta);
        letter.setPosition(xPos + i * charSize * 0.8f, yPos);
        letters.push_back(letter);
    }
}

void ColorfulText::update(float deltaTime) {
    colorTimer += deltaTime;
    if (colorTimer >= COLOR_CHANGE_INTERVAL) {
        colorTimer = 0.0f;
        updateColors();
    }
}

void ColorfulText::updateColors() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, 255);

    for (auto& letter : letters) {
        letter.setFillColor(sf::Color(
            static_cast<sf::Uint8>(dis(gen)),
            static_cast<sf::Uint8>(dis(gen)),
            static_cast<sf::Uint8>(dis(gen)))
        );
    }
}

void ColorfulText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& letter : letters) {
        target.draw(letter, states);
    }
}

void ColorfulText::setPosition(const sf::Vector2f& position, bool centerHorizontally, bool centerVertically) {
    float totalWidth = letters.size() * letters[0].getCharacterSize() * 0.8f;
    float xPos = position.x;
    float yPos = position.y;

    if (centerHorizontally) {
        xPos = position.x - totalWidth / 2.0f;
    }
    if (centerVertically) {
        yPos = position.y - letters[0].getCharacterSize() / 2.0f;
    }

    for (size_t i = 0; i < letters.size(); ++i) {
        letters[i].setPosition(xPos + i * letters[0].getCharacterSize() * 0.8f, yPos);
    }
}