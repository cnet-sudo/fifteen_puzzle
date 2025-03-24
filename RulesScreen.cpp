#include "RulesScreen.h"
#include <stdexcept>
#include <iostream>
#include "ResourceManager.h"

constexpr float TITLE_Y_POS = 15.0f;

RulesScreen::RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : window(window), state(state), transition(transition) {
    // Получаем экземпляр ResourceManager
    ResourceManager& rm = ResourceManager::getInstance();

    // Загрузка текстуры фона из ResourceManager
    sf::Texture& bgTexture = rm.getTexture("background1");
    if (bgTexture.getSize().x == 0) {  // Проверка на пустую текстуру
        std::cerr << "Ошибка: Не удалось загрузить фон 'background1' из ResourceManager.\n";
    }
    backgroundSprite.setTexture(bgTexture);

    // Получение шрифтов из ResourceManager
    sf::Font& font = rm.getFont("font");    // Предполагается "font" - это arial.ttf
    sf::Font& font2 = rm.getFont("font1");  // Предполагается "font1" - это glv.ttf

    // Проверка успешной загрузки шрифтов
    if (font.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font' из ResourceManager");
    }
    if (font2.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font1' из ResourceManager");
    }

    // Настройка заголовка с изменением цвета
    titleText = std::make_unique<ColorfulText>("font1", L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    // Настройка текста с правилами
    text.setFont(font);
    text.setString(
        L"   1. Игровое поле состоит из 15 пронумерованных\n"
        L"   плиток и одного пустого места.\n"
        L"   2. Цель игры перемещая плитки, расположить\n"
        L"   их в правильном порядке: (см. изображение справа)\n"
        L"   3. Перемещать можно только плитки,\n"
        L"   соседние с пустым местом.\n"
        L"   4. Используйте для перемещения плиток левую кнопку\n"
        L"   мыши.\n\n"
        L"   Удачи!"
    );
    text.setCharacterSize(30);  // Увеличенный размер текста
    text.setFillColor(sf::Color::Black);

    // Центрирование текста
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(0, text.getLocalBounds().height / 2.0f); // Убираем центрирование по X
    text.setPosition(30.0f, window.getSize().y / 2.0f); // Устанавливаем ближе к левому краю

    // Создание полупрозрачного светлого фона под текст
    textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 60));
    textBackground.setFillColor(sf::Color(255, 255, 255, 200));
    textBackground.setOrigin(0, textBackground.getSize().y / 2.0f); // Убираем центрирование по X
    textBackground.setPosition(20.0f, window.getSize().y / 2.0f + 10.0f); // Синхронизация с текстом

    // Загрузка изображения с цифрами из ResourceManager
    sf::Texture& numTexture = rm.getTexture("numbers");
    if (numTexture.getSize().x == 0) {  // Проверка на пустую текстуру
        std::cerr << "Ошибка: Не удалось загрузить изображение 'numbers' из ResourceManager.\n";
    }
    numbersSprite.setTexture(numTexture);
    sf::FloatRect numbersRect = numbersSprite.getLocalBounds();
    numbersSprite.setOrigin(numbersRect.width / 2.0f, numbersRect.height / 2.0f);
    numbersSprite.setScale(0.9f, 0.9f); // Уменьшение изображения на 10%
    numbersSprite.setPosition(window.getSize().x * 0.75f + 100, window.getSize().y / 2.0f);

    // Создание кнопки в стиле GameScreen
    backButton = std::make_unique<Button>(
        std::wstring(L"м е н ю"),
        sf::Vector2f(445, 600),
        font,
        sf::Color(64, 224, 208, 255),  // Бирюзовый цвет
        sf::Color(64, 224, 208, 255),
        sf::Color::Black,
        sf::Color(128, 128, 128),
        395.0f,
        50.0f,
        30u,
        sf::Color::Black,
        4.0f
    );
}

void RulesScreen::handleEvent(const sf::Event& event) {
    // Обработка нажатия Esc для перехода в меню
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        transition.startTransition(GameState::MENU);
    }

    // Обработка нажатия кнопки мыши
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->pressAnimation();
        }
    }

    // Обработка отпускания кнопки мыши
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->releaseAnimation();
            transition.startTransition(GameState::MENU);
        }
    }
}

void RulesScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::White);         // Очистка экрана белым цветом
    target.draw(backgroundSprite, states);  // Отрисовка фоновой текстуры
    target.draw(textBackground, states);    // Отрисовка полупрозрачного фона под текст
    target.draw(numbersSprite, states);     // Отрисовка изображения с цифрами
    target.draw(text, states);             // Отрисовка текста с правилами
    target.draw(*backButton, states);      // Отрисовка кнопки
    titleText->draw(target, states);       // Отрисовка заголовка
}

void RulesScreen::update(float deltaTime) {
    titleText->update(deltaTime);  // Обновление анимации заголовка
}