#include "RulesScreen.h"
#include <stdexcept>
#include <iostream>

constexpr float TITLE_Y_POS = 15.0f;

RulesScreen::RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : window(window), state(state), transition(transition) {
    // Загрузка текстуры фона
    if (!backgroundTexture.loadFromFile("background1.png")) {
        std::cerr << "Ошибка: Не удалось загрузить фон 'background1.png'.\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Загрузка шрифта arial
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Не удалось загрузить шрифт arial.ttf");
    }

    // Загрузка шрифта для заголовка (как в GameScreen)
    if (!font2.loadFromFile("glv.ttf")) {
        throw std::runtime_error("Не удалось загрузить шрифт glv.ttf");
    }

    // Настройка заголовка с изменением цвета
    titleText = std::make_unique<ColorfulText>(font2, L"Правила игры", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    // Настройка текста с правилами (группа цифр заменена на изображение)
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
    text.setPosition(30.0f, window.getSize().y / 2.0f ); // Устанавливаем ближе к левому краю (20 пикселей от края)

    // Создание полупрозрачного светлого фона под текст
    textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 60));
    textBackground.setFillColor(sf::Color(255, 255, 255, 200));
    textBackground.setOrigin(0, textBackground.getSize().y / 2.0f); // Убираем центрирование по X
    textBackground.setPosition(20.0f, window.getSize().y / 2.0f + 10.0f); // Синхронизация с текстом

    // Загрузка изображения с цифрами
    if (!numbersTexture.loadFromFile("numbers.png")) {
        std::cerr << "Ошибка: Не удалось загрузить изображение 'numbers.png'.\n";
    }
    numbersSprite.setTexture(numbersTexture);
    sf::FloatRect numbersRect = numbersSprite.getLocalBounds();
    numbersSprite.setOrigin(numbersRect.width / 2.0f, numbersRect.height / 2.0f);
    // Уменьшение изображения на 10 % (масштаб 0.9)
        numbersSprite.setScale(0.9f, 0.9f);
    // Смещение вправо: установка позиции ближе к правому краю окна
    numbersSprite.setPosition(window.getSize().x * 0.75f+100, window.getSize().y / 2.0f );
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