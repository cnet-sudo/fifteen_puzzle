#include "ColorfulText.h"
#include "ResourceManager.h"
#include <algorithm>
#include <random>

// Конструктор
ColorfulText::ColorfulText(const std::string& fontId, std::wstring_view text, unsigned int charSize,
    const sf::Vector2f& position, const sf::RenderWindow& window,
    bool centerHorizontally, bool centerVertically)
    : colorTimer(0.0f) {

    // Получаем ссылку на синглтон ResourceManager
    ResourceManager& rm = ResourceManager::getInstance();

    // Загружаем шрифт
    font = std::make_shared<sf::Font>(rm.getFont(fontId));

    // Проверяем, загрузился ли шрифт
    if (font->getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт с ID: " + std::string(fontId) + " из ResourceManager");
    }

    // Вычисляем общую ширину текста для центрирования
    float totalWidth = text.size() * charSize * 0.8f;
    float xPos = position.x;
    float yPos = position.y;

    if (centerHorizontally) {
        xPos = (window.getSize().x - totalWidth) / 2.0f;
    }
    if (centerVertically) {
        yPos = (window.getSize().y - charSize) / 2.0f;
    }

    // Создаем отдельные буквы и задаем им позицию и цвет
    letters.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        sf::Text letter;
        letter.setFont(*font);
        letter.setString(text[i]); // Каждая буква отдельно
        letter.setCharacterSize(charSize);
        letter.setFillColor(sf::Color::Magenta); // Начальный цвет
        letter.setPosition(xPos + i * charSize * 0.8f, yPos);
        letters.push_back(letter);
    }
}

// Обновление — вызывается каждый кадр, меняет цвет по таймеру
void ColorfulText::update(float deltaTime) {
    colorTimer += deltaTime;
    if (colorTimer >= COLOR_CHANGE_INTERVAL) {
        colorTimer = 0.0f;
        updateColors();
    }
}

// Функция случайной смены цвета каждой буквы
void ColorfulText::updateColors() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, 255);

    for (auto& letter : letters) {
        letter.setFillColor(sf::Color(
            static_cast<sf::Uint8>(dis(gen)),  // R
            static_cast<sf::Uint8>(dis(gen)),  // G
            static_cast<sf::Uint8>(dis(gen))   // B
        ));
    }
}

// Отрисовка всех букв текста
void ColorfulText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& letter : letters) {
        target.draw(letter, states);
    }
}

// Установка новой позиции текста с опциональным центрированием
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

    // Обновляем позицию каждой буквы
    for (size_t i = 0; i < letters.size(); ++i) {
        letters[i].setPosition(xPos + i * letters[0].getCharacterSize() * 0.8f, yPos);
    }
}
